

def main():
    text = input("Text: ")

    # Compute Coleman-Liau index
    index = coleman_index(text);

    # Show grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def coleman_index(text):
    words = 0
    sentences = 0
    letters = 0
    # Count letters, words, sentences
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
        elif (text[i] == '.' or text[i] == '!' or text[i] == '?'):
            sentences += 1
        elif text[i]==" ":
            words += 1
    words += 1

    # Count avarage leters in 100 words
    avg_letters = letters / words * 100
    # Count avarage sentences in 100 words
    avg_sentences = sentences / words * 100
    index = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)
    return index

main()
