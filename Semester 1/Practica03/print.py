uc= ["UI", "SIM", "-", "SARM", "UP", "-", "-", "SABM", "DISC", "-", "-", "SARME", "- ", "-", "-", "SABME", "SNRM", "-   ", "-", "RSET", "-", "-", "-", "XID", "-", "-", "-", "SNRME", "-", "-", "-", "-"]
ur = ["UI", "RIM", "-", "DM  ", "- ", "-", "-", "-   ", "RD  ", "-", "-", "-    ", "UA", "-", "-", "-    ", "-   ", "FRMR", "-", "-   ", "-", "-", "-", "XID", "-", "-", "-", "-    ", "-", "-", "-", "-"]


for i in range(len(uc)):
    print("{:2}".format(i)," | ",uc[i].replace(' ','').center(7),' | ',ur[i].replace(' ','').center(7))
