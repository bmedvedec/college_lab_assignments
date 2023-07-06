import urllib.request
import re
import argparse


def findAllLinks(stranica):
    links = re.findall(r'href="([^"]+)"', stranica)
    return links


def findAllHosts(links):
    hosts = set()

    for link in links:
        host = urllib.parse.urlparse(link).hostname

        if host:
            hosts.add(host)

    return hosts


def findAllEmails(stranica):
    emails = re.findall(r"[\w\.-]+@[\w\.-]+", stranica)

    return emails


def findAllImages(stranica):
    images = re.findall(r'<img src="([^">]+)"', stranica)
    return images


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("url", help="url adresa")

    args = parser.parse_args()

    url = args.url

    try:
        stranica = urllib.request.urlopen(url)
        mybytes = stranica.read()
        mystr = mybytes.decode("utf8")
    except:
        print("Ne mogu otvoriti url adresu")
        exit()

    print(f"Web stranica {url}:")
    print(mystr)

    links = findAllLinks(mystr)
    print("\nLinkovi na stranici:")
    for link in links:
        print(link)

    hosts = findAllHosts(links)
    print("\nHostovi na stranici:")
    for host in hosts:
        print(host)

    print("\nBroj referenci na hostove:")
    for host in hosts:
        print(f"{host}: {mystr.count(host)}")

    emails = findAllEmails(mystr)
    print("\nEmail adrese na stranici:")
    for email in emails:
        print(email)

    images = findAllImages(mystr)
    print(f"\nBroj slika na stranici: {len(images)}")


if __name__ == "__main__":
    main()
