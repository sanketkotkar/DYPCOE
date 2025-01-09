# Initialize hash table
hash_table = [None] * 10

def hash_function(key):
    return key % 10

def insert(key, value):
    index = hash_function(key)
    if hash_table[index] is None:
        hash_table[index] = []
    for pair in hash_table[index]:
        if pair[0] == key:
            pair[1] = value
            return
    hash_table[index].append([key, value])

def delete(key):
    index = hash_function(key)
    if hash_table[index] is not None:
        for i in range(len(hash_table[index])):
            if hash_table[index][i][0] == key:
                hash_table[index].pop(i)
                return "Key " + str(key) + " deleted."
    return "Key " + str(key) + " not found."

def search(key):
    index = hash_function(key)
    if hash_table[index] is not None:
        for pair in hash_table[index]:
            if pair[0] == key:
                return pair[1]
    return "Key not found."

# Display hash table
def display():
    for i in range(len(hash_table)):
        print("Index", i, ":", hash_table[i])

# Menu-driven program
def main():
    while True:
        print("\nHash Table Operations Menu:")
        print("1. Insert")
        print("2. Delete")
        print("3. Search")
        print("4. Display")
        print("5. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            key = int(input("Enter key to insert: "))
            value = input("Enter value to insert: ")
            insert(key, value)
            print("Key", key, "with value", value, "inserted.")
        elif choice == 2:
            key = int(input("Enter key to delete: "))
            print(delete(key))
        elif choice == 3:
            key = int(input("Enter key to search: "))
            result = search(key)
            print("Search result:", result)
        elif choice == 4:
            print("Current hash table:")
            display()
        elif choice == 5:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
