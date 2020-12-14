#!/usr/bin/env python

"""
Extract solved problems (https://leetcode.com/problemset/all/?status=Solved) to populate README markdown.
"""

import argparse
from bs4 import BeautifulSoup
import glob
import io
import os


class LeetCode:
    def __init__(self):
        pass

    def parse_html(self, html_file, cpp_dir):
        soup = None
        with io.open(file=html_file, encoding="UTF-8") as fd:
            soup = BeautifulSoup(fd, "html5lib")

        assert soup is not None, "Unable to parse {}".format(html_file)
        table = soup.find('table', attrs={'class': 'table table-striped'})
        assert table is not None, "Unable to extract table"

        # extract table columns
        title_col_index = None
        problem_number_col_index = None

        thead = table.find('thead')
        assert thead is not None, "Unable to extract thead"

        for i, th in enumerate(thead.findAll('th')):
            if th is None:
                continue
            if th.string == "#":
                problem_number_col_index = i
            elif th.string == "Title":
                title_col_index = i

        cpp_files = glob.glob("./*.cpp")

        assert problem_number_col_index is not None, "Failed to extract problem_number_col_index"
        assert title_col_index is not None, "Failed to extract title_col_index"

        for tbody in table.findAll('tbody', attrs={'class': "reactable-data"}):
            for tr in tbody.findAll('tr'):
                problem_id = None
                problem_descriptive_name = None
                problem_short_name = None
                problem_url = None

                for td_i, td in enumerate(tr.findAll('td')):
                    if td_i == problem_number_col_index:
                        problem_id = td.string
                    elif td_i == title_col_index:
                        problem_descriptive_name = td['value']
                        problem_url = td.div.a['href']
                        problem_short_name = td.div.a['data-slug']

                cpp_filename = os.path.join(cpp_dir, problem_short_name.replace("-", "_") + ".cpp")

                print('|{0}|[{1}]({2})|[C++]({3})|'.format(problem_id, problem_descriptive_name, problem_url, cpp_filename if os.path.exists(cpp_filename) else None))



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--html_file", action="store", default="C:/KA/(2) Problems - LeetCode.html", dest="html_file")
    parser.add_argument("--cpp_dir", action="store", default="./src/", dest="cpp_dir")
    args = parser.parse_args()

    print("args: {}".format(args))

    leetcode_obj = LeetCode()
    leetcode_obj.parse_html(html_file=args.html_file, cpp_dir=args.cpp_dir)
