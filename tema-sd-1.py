import random
import time

lista_sortari = ["Radix", "Merge", "Shell", "Counting", "Quick", "Tim"]

def initVector(N, NMAX):
    v = []
    for i in range(N):
        v.append(random.randint(0, NMAX))
    return v

def verifySort():
    if v == sorted(vOriginal):
        return True
    return False

def citireFisier():
    with open("tema-sd-1.txt") as f:
        f = [int(x) for x in f.read().split()]
    selector_sortari = f[0]
    f = f[1:]
    tmp = []
    for i in range(0, len(f), 2):
        tmp.append((f[i], f[i + 1]))
    return selector_sortari, tmp

def radixSort(v, radix):
    p = 1
    maxx = max(v)

    while p <= maxx:
        buckets = []
        for i in range(radix):
            buckets.append([])
        for element in v:
            cifra = element // p % radix
            buckets[cifra].append(element)
        v = []
        for bList in buckets:
            for bItem in bList:
                v.append(bItem)
        p *= radix

    return v

def mergeSort(v):
    if len(v) > 1:
        mid = len(v) // 2

        st = v[:mid]
        dr = v[mid:]

        mergeSort(st)
        mergeSort(dr)

        i = 0
        j = 0
        d = 0
        while i < len(st) and j < len(dr):
            if st[i] < dr[j]:
                v[d] = st[i]
                i += 1
            else:
                v[d] = dr[j]
                j += 1
            d += 1

        while i < len(st):
            v[d] = st[i]
            i += 1
            d += 1
        while j < len(dr):
            v[d] = dr[j]
            j += 1
            d += 1
            
def shellSort(v):
    mid = len(v) // 2

    while mid > 0:
        for j in range(mid, len(v)):
            i = j - mid

            while i >= 0:
                if v[i + mid] > v[i]:
                    break
                else:
                    v[i + mid], v[i] = v[i], v[i + mid]
                i = i - mid
        mid = mid // 2

def countSort(v):
    count = [0] * (NMAX + 1)
    k = 0
    for element in v:
        count[element] += 1
    for i in range(NMAX + 1):
        for j in range(count[i]):
            v[k] = i
            k += 1

def quick(low, high):
    if low < high:
        j = low
        i = low - 1
        while j < high:
            if v[j] < v[high]:
                i += 1
                aux = v[i]
                v[i] = v[j]
                v[j] = aux
            j += 1
        aux = v[i + 1]
        v[i + 1] = v[high]
        v[high] = aux
        quick(low, i)
        quick(i + 2, high)

def quickSort(v):
    if len(v) <= 1:
        return v
    else:
        pivot = median_of_three(v)
        less = [x for x in v if x < pivot]
        equal = [x for x in v if x == pivot]
        greater = [x for x in v if x > pivot]
        return quickSort(less) + equal + quickSort(greater)

def median_of_three(v):
    first = v[0]
    last = v[-1]
    middle = v[len(v) // 2]
    if first <= middle <= last or last <= middle <= first:
        return middle
    elif middle <= first <= last or last <= first <= middle:
        return first
    else:
        return last

selector_sortari, teste = citireFisier()

for tuplu in teste:
    N = tuplu[0]
    NMAX = tuplu[1]

    #N = 10000000
    #v = [1] * N
    v = initVector(N, NMAX)

    vOriginal = v.copy()
    start_time = time.time()

    if selector_sortari == 0:
        #v = radixSort(v, 16)
        v = radixSort(v, 32768)
    elif selector_sortari == 1:
        mergeSort(v)
    elif selector_sortari == 2:
        shellSort(v)
    elif selector_sortari == 3:
        countSort(v)
    elif selector_sortari == 4:
        v = quickSort(v)
    elif selector_sortari == 5:
        v.sort()

    end_time = time.time()
    print(verifySort(), "\t{}\t{}\t".format(N, NMAX), lista_sortari[selector_sortari] + "\t{}".format(end_time - start_time))

#print(vOriginal, v, sep = "\n")
