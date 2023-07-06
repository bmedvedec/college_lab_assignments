#!/usr/bin/env python3
import sys
import os
import json
import string

from Crypto.Cipher import AES
from Crypto.Protocol.KDF import scrypt
from Crypto.Random import get_random_bytes


class Tajnik:
    def __init__(self, masterPassword):
        self.data = {}
        self.masterPassword = masterPassword

    def init(self):
        # check if database already exists
        if os.path.exists("tajnik.db"):
            sys.exit("Password manager already initialized")
        # initialize database with empty dictionary
        else:
            plaintext = json.dumps(self.data).encode("utf-8")
            salt, nonce, tag, ciphertext = self.encrypt(plaintext)

            try:
                self.write_to_db(salt, nonce, tag, ciphertext)
            except IOError:
                sys.exit("Cannot write to database")

            print("Password manager initialized")

    def put(self, address, password):
        # read from database
        try:
            salt, nonce, tag, ciphertext = self.read_from_db()
        except IOError:
            sys.exit("Cannot read from database")

        # decrypt database
        try:
            plaintext = self.decrypt(salt, nonce, tag, ciphertext)
        except ValueError:
            sys.exit("Master password incorrect or integrity check failed")

        # store [address, password] pair in dictionary
        self.data = json.loads(plaintext)
        self.data[address] = password
        plaintext = json.dumps(self.data).encode("utf-8")

        # encrypt database
        salt, nonce, tag, ciphertext = self.encrypt(plaintext)

        # write to database
        try:
            self.write_to_db(salt, nonce, tag, ciphertext)
        except IOError:
            sys.exit("Cannot write to database")

        print("Stored password for " + address)

    def get(self, address):
        # read from database
        try:
            salt, nonce, tag, ciphertext = self.read_from_db()
        except IOError:
            sys.exit("Cannot read from database")

        # decrypt database
        try:
            plaintext = self.decrypt(salt, nonce, tag, ciphertext)
        except ValueError:
            sys.exit("Master password incorrect or integrity check failed")

        # load dictionary and print password for given address
        self.data = json.loads(plaintext)
        if address in self.data:
            print("Password for " + address + " is: " + self.data[address])
        else:
            print("No password for " + address)

    def write_to_db(self, salt, nonce, tag, ciphertext):
        with open("tajnik.db", "wb") as f:
            f.write(salt)
            f.write(nonce)
            f.write(tag)
            f.write(ciphertext)

    def read_from_db(self):
        with open("tajnik.db", "rb") as f:
            salt = f.read(16)
            nonce = f.read(16)
            tag = f.read(16)
            ciphertext = f.read()

        return salt, nonce, tag, ciphertext

    def encrypt(self, plaintext):
        salt = get_random_bytes(16)  # generate random 16-byte (128 bit) salt
        nonce = get_random_bytes(16)  # generate random 16-byte (128 bit) nonce
        # generate 32-byte (256 bit) key from master password and salt
        key = scrypt(self.masterPassword, salt, key_len=32, N=2**14, r=8, p=1)
        # initialize AES-GCM cipher
        cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
        ciphertext, tag = cipher.encrypt_and_digest(
            plaintext)  # encrypt plaintext and generate tag

        return salt, nonce, tag, ciphertext

    def decrypt(self, salt, nonce, tag, ciphertext):
        key = scrypt(self.masterPassword, salt, key_len=32, N=2**14, r=8, p=1)
        cipher = AES.new(key, AES.MODE_GCM, nonce=nonce)
        # decrypt ciphertext and verify tag
        plaintext = cipher.decrypt_and_verify(ciphertext, tag)

        return plaintext


def callError(no_args, target):
    if no_args < target:
        sys.exit("Inccorect number of arguments")


def main():
    callError(len(sys.argv), 3)

    action = sys.argv[1]
    masterPassword = sys.argv[2]

    if len(masterPassword) < 10:
        sys.exit("Master password must be at least 10 characters long")
    elif (not any(char.isdigit() for char in masterPassword)
          or not any(char.isupper() for char in masterPassword)
          or not any(char.islower() for char in masterPassword)
          or not any(char in string.punctuation for char in masterPassword)):
        sys.exit("Master password must contain at least one digit, one uppercase letter, one lowercase letter and one special character")

    tajnik = Tajnik(masterPassword)

    if action == "init":
        tajnik.init()
    elif action == "put":
        callError(len(sys.argv), 5)

        address = sys.argv[3]
        password = sys.argv[4]

        tajnik.put(address, password)
    elif action == "get":
        callError(len(sys.argv), 4)

        address = sys.argv[3]
        tajnik.get(address)


if __name__ == "__main__":
    main()
