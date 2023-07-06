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


class UserMgmt:
    def __init__(self):
        self.data = {}

        # create database if it doesn't exist, otherwise read it
        if not os.path.exists(DATABASE):
            try:
                with open(DATABASE, "wb") as f:
                    pass
            except IOError:
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

    def add(self, username):
        # check if user already exists
        if username in self.data:
            sys.exit("User add failed.")

        user = User(username, "", False)

        # password prompt
        password = getpass.getpass("Password: ")
        password2 = getpass.getpass("Repeat password: ")

        if password != password2:
            sys.exit("User add failed. Password mismatch.")

        password_check(password)  # check if password is strong enough

        # add user to database
        salt = get_random_bytes(16)
        hash_object = SHA3_512.new()
        hash_object.update(salt + password.encode("utf-8"))
        user.hash = salt.hex() + hash_object.hexdigest()

        try:
            with open(DATABASE, "ab") as f:
                f.write(
                    f"{user.username}: {user.hash}, {user.flag}\n".encode())

        except IOError:
            error()

        print(f"User {user.username} successfully added.")

    def passwd(self, username):
        if username not in self.data:
            sys.exit("Pasword change failed.")

        password = getpass.getpass("Password: ")
        password2 = getpass.getpass("Repeat password: ")

        if password != password2:
            sys.exit("Password change failed. Password mismatch.")

        password_check(password)  # check if password is strong enough

        # change password
        salt = get_random_bytes(16)
        hash_object = SHA3_512.new()
        hash_object.update(salt + password.encode("utf-8"))
        user = User(username, "", False)
        user.hash = salt.hex() + hash_object.hexdigest()

        self.data[username] = f"{user.hash}, {user.flag}"

        # update database
        self.write()

        print("Password change successful.")

    def forcePass(self, username):
        if username not in self.data:
            sys.exit("Pasword change failed.")

        user = User(username, "", True)
        user.hash = self.data[username].split(",")[0]

        self.data[username] = f"{user.hash}, {user.flag}"

        # update database
        self.write()

        print("User will be requested to change password on next login.")

    def delete(self, username):
        if username not in self.data:
            sys.exit("User delete failed.")

        # pop user from database
        self.data.pop(username)

        # update database
        self.write()

        print("User successfully removed.")

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
    parser.add_argument("action", help="Action to perform", choices=[
                        "add", "passwd", "forcepass", "del"])
    parser.add_argument("username", help="Username to add")

    args = parser.parse_args()

    usermgmt = UserMgmt()

    if args.action == "add":
        usermgmt.add(args.username)

    elif args.action == "passwd":
        usermgmt.passwd(args.username)

    elif args.action == "forcepass":
        usermgmt.forcePass(args.username)

    elif args.action == "del":
        usermgmt.delete(args.username)
