f = open('myfile.csv', 'a', encoding='UTF-8')

f.write('こんにちは\n')

datalist = ['お元気ですか？\n', 'それではまた\n']
f.writelines(datalist)

f.close()