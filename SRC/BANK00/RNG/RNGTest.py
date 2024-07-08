def main():
    finds = {}

    for v in range(261 + 1):
        for h in range(339 + 1):
            res = ((v % 255) ^ 255) ^ (h % 255)
            finds[res] = finds.get(res, 0) + 1

    print(f"# of unique numbers: {len(finds)}")
    print(finds)

if __name__ == "__main__":
    main()
