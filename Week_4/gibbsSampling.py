def BuildProfileMatrix(dnamatrix):
    ProfileMatrix = [[1 for x in range(len(dnamatrix[0]))] for x in range(4)]
    indices = {'A':0, 'C':1, 'G': 2, 'T':3}
    for seq in dnamatrix:
        for i in range(len(dnamatrix[0])):            
            ProfileMatrix[indices[seq[i]]][i] += 1

    # print([sum(x) for x in zip(*ProfileMatrix)])
            
    ProbMatrix = [[float(x)/[sum(x) for x in zip(*ProfileMatrix)][i] for i, x in enumerate(y)] for y in ProfileMatrix]
    return ProbMatrix

def ProfileRandomGenerator(profile, dna, k, i):
    indices = {'A':0, 'C':1, 'G': 2, 'T':3}
    score_list = []
    for x in range(len(dna[i]) - k + 1):
        probability = 1
        window = dna[i][x : k + x]
        for y in range(k):
            probability *= profile[indices[window[y]]][y]
        score_list.append(probability)
    rnd = uniform(0, sum(score_list))
    current = 0
    for z, bias in enumerate(score_list):
        current += bias
        if rnd <= current:
            return dna[i][z : k + z]

def score(motifs):
    ProfileMatrix = [[0 for x in range(len(motifs[0]))] for x in range(4)]
    indices = {'A':0, 'C':1, 'G': 2, 'T':3}
    for seq in motifs:
        for i in range(len(motifs[0])):            
            ProfileMatrix[indices[seq[i]]][i] += 1
    score = len(motifs)*len(motifs[0]) - sum([max(x) for x in zip(*ProfileMatrix)])
    return score

from random import randint, uniform 

def GibbsSampler(k, t, N):
    dna = ['CGCCCCTCTCGGGGGTGTTCAGTAACCGGCCA',
    'GGGCGAGGTATGTGTAAGTGCCAAGGTGCCAG',
    'TAGTACCGAGACCGAAAGAAGTATACAGGCGT',
    'TAGATCAAGTTTCAGGTGCACGTCGGTGAACC',
    'AATCCACCAGCTCCACGTGCAATGTTGGCCTA']
    Motifs = []
    for i in [randint(0, len(dna[0])-k) for x in range(len(dna))]:
        j = 0
        kmer = dna[j][i : k+i]
        j += 1
        Motifs.append(kmer)
    BestMotifs = []
    s_best = float('inf')
    for i in range(N):
        x = randint(0, t-1)
        Motifs.pop(x)
        profile = BuildProfileMatrix(Motifs)
        Motif = ProfileRandomGenerator(profile, dna, k, x)
        Motifs.insert(x, Motif)
        s_motifs = score(Motifs)
        if s_motifs < s_best:
            s_best = s_motifs
            BestMotifs = Motifs
    return [s_best, BestMotifs]

k, t, N =8, 5, 100            
best_motifs = [float('inf'), None]

# Repeat the Gibbs sampler search 20 times.
for repeat in range(20):
    current_motifs = GibbsSampler(k, t, N)
    if current_motifs[0] < best_motifs[0]:
        best_motifs = current_motifs
# Print and save the answer.
print('\n'.join(best_motifs[1]))