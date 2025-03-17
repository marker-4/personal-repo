alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"

def vigenereCipherForward(message, key): #encrypts a message with a given keyword with vigenere cipher
    shiftedMessage = vigenereShift(message, key) #gets values for message and shifts them by keyword
    encryptedMessage = valuesToMessage(shiftedMessage) #converts shifted values back to letters
    
    for i in range(len(message)): #fixes capitals
        if message[i].isupper():
            encryptedMessage = encryptedMessage[:i] + encryptedMessage[i].capitalize() + encryptedMessage[i+1:]
    return encryptedMessage

def getNumericValue(character): #Converts characters of alphabet into their associated numbers while leaving non-letter characters as they are
    
    global alphabet
    index = 0 #tracks index of character in string with variable
    if character in alphabet: #allows function to be used for ",", " ", ":", etc. characters
        for letter in alphabet:
            if character == letter:
                letterValue = index // 2 #gives upper and lowercase letters produce same output
                return str(letterValue)
            else:
                index += 1
    else:
        return character

def messageToValues(message): #turns all letters to numbers and separates every character/number with "/+/"
    messageOfValues = ""
    for ch in message:
        messageOfValues += getNumericValue(ch) + "/+/"
    return messageOfValues

def makeList(string): #turns strings into a list of vigenere values, ignoring other characters
    messageOfValues = messageToValues(string)
    listOfValues = []
    while messageOfValues.find("/+/") > -1:
        endOfObj = messageOfValues.find("/+/")
        obj = messageOfValues[:endOfObj]
        if obj.isnumeric():
            listOfValues.append(obj)
        else:
            listOfValues.append(obj)
            
        messageOfValues = messageOfValues[(endOfObj + 3):]
    return listOfValues

def vigenereShift(message, key): #shifts alpha letters in message by values from keyword, ignoring special characters
    messageOfList = makeList(message)
    keyOfList = makeList(key)
    keyInd = 0
    encryptedMessageValues = []
    for value in messageOfList: 
        if value.isnumeric():
            newValue = int(value) + int(keyOfList[keyInd]) #adds value from keyword value list to message value if value is numeric
            if newValue >= 26: #keeps character between 0 and 25
                newValue -= 26
            encryptedMessageValues.append(str(newValue))
            keyInd += 1 #moves moves key index to next index value
            if keyInd == len(keyOfList):
                keyInd = 0 #moves index back to 0 when it exceeds the index max
        else:
            encryptedMessageValues.append(value)
    return encryptedMessageValues

def valuesToMessage(encryptedMessageValues): #converts a list of values to latin script
    global alphabet
    message = ""
    for obj in encryptedMessageValues:
        if obj.isnumeric():
            value = int(obj)
            index = value * 2 + 1
            message += alphabet[index]
        else:
            message += obj
    return message
    
message = input("What message would you like to encrypt?")
key = input("What is your key?")
encodedText = vigenereCipherForward(message, key)
print("Your encoded message is: ", encodedText)