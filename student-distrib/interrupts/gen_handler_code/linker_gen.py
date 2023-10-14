handlers = []
with open("handlers.txt", "r") as f:
    for line in f:
        handlers.append(line.split()[2])

linkers = [h[:-10]+"linkage" for h in handlers]
# print(', '.join([h[:-3] for h in handlers]))
# print(', '.join(linkers))

with open("set_idt.c", "w") as f:
    for l in linkers:
        # need to fill in addresses manually to account for reserved addr
        s = f"SET_IDT_ENTRY(idt[__], {l});\n"
        f.write(s)

with open("linkage.asm", "w") as f:
    for h in handlers:
        l = h[:-10]
        l += "linkage"
        s = f"""
{l}:
    pushal
    pushfl
    call {h[:-3]}
    popfl
    popal
    iret
        """
        f.write(s)
