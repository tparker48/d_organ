file = open("Linear to Logarithmic Lookup Table.txt",'w')
file.write('\\\\ This auto-generated file provides a lookup table for converting the linear potentiometer readings to a logarithmic scale\n')
file.write('int lin2log[1024] = {\n')

comma = ','

lookup = []
for i in range(1024):
    lookup.append(.25*(5**(i/1023.0))-.25)
    print(lookup[i])
    if(i==1023):
        comma = ''
    file.write(str(lookup[i]) + comma)