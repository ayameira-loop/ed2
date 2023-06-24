def constroi(alphabet, pattern):
    dfa = [[0] * len(pattern) for _ in range(len(alphabet))]
    dfa[getStateNumber(alphabet, pattern, 0)][0] = 1
    x = 0
    j = 1
    m = len(pattern)
    tam = len(alphabet)
    while j < m:
        c = 0
        while c < tam:
            dfa[c][j] = dfa[c][x]
            c+= 1
        dfa[getStateNumber(alphabet, pattern, j)][j] = j + 1
        x = dfa[getStateNumber(alphabet, pattern, j)][x]
        j+=1
        
    #for i in range (len(dfa)):
    #    print (dfa[i])
    
    return dfa
    
    
def getStateNumber(alphabet, pattern, idx):
    symbol = pattern[idx]
    return alphabet.index(symbol)

def kmp(alphabet, pattern, text):
    dfa = constroi(alphabet, pattern)
    

alphabet = ['A', 'C', 'G', 'T']
pattern = 'AACATAACG'
pattern = 'TTTTTT'
pattern = 'ATAATAAAT'
constroi(alphabet, pattern)