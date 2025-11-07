import re, requests
text = requests.get("https://docs.lvgl.io/master/searchindex.js").text
seen = set()
for match in re.finditer(r"'([^']*xml[^']*)'", text, re.I):
    s = match.group(1)
    if s in seen:
        continue
    seen.add(s)
    print(s)
    if len(seen) >= 30:
        break
