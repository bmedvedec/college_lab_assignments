#!/usr/bin/env python
import sys
import argparse
import os
import getpass
import string

from Crypto.Random import get_random_bytes
from Crypto.Hash import SHA3_512


DATABASE = "users.db"


class User:
    def __init__(self, username, hash, flag):
        self.username = username
        self.hash = hash
        self.flag = flag


class Login:
    def __init__(self):
        self.data = {}

        # create database if it doesn't exist, otherwise read it
        if not os.path.exists(DATABASE):
            error()
        else:
            try:
                with open(DATABASE, "rb") as f:
                    lines = f.read().split(b'\n')

                    for line in lines:
                        user = line.decode().split(":")

                        if len(user) == 1:  # empty line
                            continue

                        self.data[user[0]] = user[1]

            except IOError:
                error()

    def login(self, username):
        # check if user exists
        if username not in self.data:
            error()

        user = User(username, "", False)
        temp = self.data[username].split(",")
        user.hash = temp[0].strip()
        user.flag = temp[1].strip()

        # check if password is correct
        hash_object = SHA3_512.new()
        # first 32 chars (16 bytes) is salt
        salt = bytes.fromhex(user.hash[:32])
        hash_password = user.hash[32:]  # rest is hashed password

        # check if password is correct
        counter = 1
        while counter <= 3:
            password = getpass.getpass("Password: ")
            hash_login_password = SHA3_512.new()
            hash_login_password.update(salt + password.encode("utf-8"))

            if hash_login_password.hexdigest() == hash_password:
                break

            print("Username or password incorrect.")
            counter += 1
            if counter == 4:
                sys.exit("Too many failed login attempts.")

        if user.flag == "True":
            user.flag = False  # reset flag
            password = getpass.getpass("New password: ")
            password2 = getpass.getpass("Repeat new password: ")

            if password != password2:
                sys.exit("Password change failed. Password mismatch.")

            # check if password is strong enough
            password_check(password)

            # change password
            hash_object = SHA3_512.new()
            salt = get_random_bytes(16)
            hash_object.update(salt + password.encode("utf-8"))
            user.hash = salt.hex() + hash_object.hexdigest()

            # update database
            self.data[user.username] = f"{user.hash}, {user.flag}"

            self.write()

        print("Login successful.")

    def write(self):
        try:
            with open(DATABASE, "w") as f:
                for user in self.data:
                    f.write(f"{user}: {self.data[user]}\n")

        except IOError:
            error()


def error():
    sys.exit("Error, please try again!")


def password_check(password):
    if len(password) < 10:
        sys.exit("Password must be at least 10 characters long.")
    elif (not any(char.isdigit() for char in password)
          or not any(char.isupper() for char in password)
          or not any(char.islower() for char in password)
          or not any(char in string.punctuation for char in password)):
        sys.exit("Password must contain at least one digit, one uppercase letter, one lowercase letter and one special character.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("username", help="Username to login with")

    args = parser.parse_args()

    login = Login()

    login.login(args.username)
