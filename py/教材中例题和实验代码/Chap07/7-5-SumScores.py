import openpyxl
from openpyxl.styles import Font, Side, Border
# 打开工作表'一班'
scores_excel = openpyxl.load_workbook(r'scores_all.xlsx')
scores_excel_sheet = scores_excel['一班']
# 设置边框样式
side = Side(border_style='thin')#border_style='thin', color='00FF0000'
# 设置标题栏内容、样式
scores_excel_sheet['E1'] = '总分'
scores_excel_sheet['E1'].font = Font(bold=True)
scores_excel_sheet['E1'].border = Border(top=side, bottom=side, left=side, right=side)
# 设置内容栏内容、样式
for row in range(2, scores_excel_sheet.max_row + 1):
    row_str = str(row)
    scores_excel_sheet['E' + row_str] = '=SUM(B' + row_str + ':D' + row_str + ')'
    # scores_excel_sheet['E'+ row_str].font = Font(name='宋体')
    scores_excel_sheet['E'+ row_str].font = Font(name='Times New Roman')# , color='0000FF00'
    scores_excel_sheet['E'+ row_str].border = Border(top=side, bottom=side, left=side, right=side)
scores_excel.save(r'scores_all_sum.xlsx')