POINTS = [
    "1S", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "11S", "12S",
    "13S", "14S", "15S", "16S", "17S", "18S", "19S", "20S", "25S",
    "2D", "4D", "6D", "8D", "10D", "12D", "14D", "16D", "18D", "20D", "22D",
    "24D", "26D", "28D", "30D", "32D", "34D", "36D", "38D", "40D", "50D",
    "3T", "6T", "9T", "12T", "15T", "18T", "21T", "24T", "27T", "30T", "33T",
    "36T", "39T", "42T", "45T", "48T", "51T", "54T", "57T", "60T"
]

def solve(darts, current_score, routes, segment):
    if darts < 0:
        return routes
    if current_score == score and segment == 'D':
        return routes + 1

    for p in POINTS:
        val = int(p[:-1])
        seg = p[-1]

        if current_score + val <= score:
            routes = solve(darts - 1, current_score + val, routes, seg)

    return routes
        

score = int(input())
darts = int(input())

routes = solve(darts, 0, 0, 'S')

print(routes)
