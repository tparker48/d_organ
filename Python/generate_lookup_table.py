file = open("Linear to Logarithmic Lookup Table.txt",'w')
file.write('// This auto-generated file provides a lookup table for converting the linear potentiometer readings to a logarithmic scale\n')
file.write('float lin2log[1024] = {\n')

comma = ','

maxInput = 1023.0
a =-1.1977797
b = 0.165122

lookup = []
for i in range(1024):
    lookup.append( a*( b**(i/maxInput) )- a)
    print(lookup[i])
    if(i==1023):
        comma = ''
    file.write(str(lookup[i]) + 'f' + comma)

file.write('};')
file.close()