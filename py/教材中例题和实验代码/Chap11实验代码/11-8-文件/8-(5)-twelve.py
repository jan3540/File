import csv
with open('sy8-5.csv', 'r', encoding='utf-8') as twelve_file:
    csv_reader = csv.reader(twelve_file)
    csv_reader_list = list(csv_reader)
    input_year = int(input("请输入年份："))
    if int(input_year) > int(csv_reader_list[0][1]):
        zodiac = csv_reader_list[(int(input_year) - int(csv_reader_list[0][1])) % 12][0]
    elif (int(csv_reader_list[0][1])-int(input_year)) % 12 == 0:
        zodiac =csv_reader_list[0][0]
    else:
        zodiac = csv_reader_list[12 - (int(csv_reader_list[0][1])-int(input_year)) % 12][0]
    print(f"{input_year}年的属相是：{zodiac}")

