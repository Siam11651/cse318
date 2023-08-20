from pylatex import Document, Tabular, MultiColumn, MultiRow
import json

formatted_algorithm_name = {"greedy": "Greedy", "semi-greedy": "Semi-Greedy", "random": "Random"}
upper_bounds_json_file = open("upper-bounds.json")
upper_bounds_json_string = "".join(upper_bounds_json_file.readlines())
upper_bounds_json_object = json.loads(upper_bounds_json_string)

def gen_table(algorithm: str):
    geometry_options = "a4paper, tmargin=1cm, lmargin=1cm"
    document = Document(geometry_options=geometry_options)
    table = Tabular("| c | c | c | c | c | c |")

    table.add_hline()
    table.add_row((MultiRow(size=2, data="g"), MultiColumn(size=5, align="| c |", data=formatted_algorithm_name[algorithm])))
    table.add_hline(2, 6)
    table.add_row(("", "Before Search", "After Search", "Local Search Iterations", "GRASP Iterations", "Upper Bound"))
    table.add_hline()

    for i in range(1, 55):
        file = open(f"out-{algorithm}/g{i}.txt")    # expecting folders with pattern out-*
        line = file.readline()
        (after_search, before_search, search_iteration) = line.split(" ")   # one line in one output file corresponding a test input data

        table.add_row((i, before_search, after_search, search_iteration, 50, upper_bounds_json_object[i - 1]))
        table.add_hline()
    
    document.append(table)
    document.generate_pdf("table-" + algorithm)

gen_table("greedy")
gen_table("semi-greedy")
gen_table("random")