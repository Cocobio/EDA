from pandas import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

dna = 'dna50MB.csv'
protein = 'protein50MB.csv'
english = 'english50MB.csv'
generic = 'generic50MB.csv'
single_char = 'single_char1MB.csv'
mismatch = 'mismatch1MB.csv'

dna_t = pd.read_csv(dna,';')
protein_t = pd.read_csv(protein,';')
english_t = pd.read_csv(english,';')
generic_t = pd.read_csv(generic,';')
single_char_t = pd.read_csv(single_char,';')
mismatch_t = pd.read_csv(mismatch,';')

boyer = '#66ec76'
kmp = '#f7c248'
bf = '#48caf7'

table = [dna_t, protein_t, english_t, generic_t, single_char_t, mismatch_t]
title = ['Texto de ADN', 'Texto de proteinas', 'Texto en ingles', 'Texto generico', 'Texto con 1 solo caracter', 'Patrones con caracteres que no pertenecian al texto']

for table_i, title_i in zip(table,title):
	plt.plot(table_i['m'], table_i['boyer'], color=boyer, label='Boyer Moore')
	plt.plot(table_i['m'], table_i['kmp'], color=kmp, label='Knuth Morris Prat')
	plt.plot(table_i['m'], table_i['time_brute'], color=bf, label='Brute Force')

	plt.ylabel('Tiempo [ms]')
	plt.xlabel('Tamaño patron')
	plt.title(title_i)
	plt.legend(loc='upper left')

	plt.show()


### Boyer Moore tests
BM = 'bm.csv'

BM_t = pd.read_csv(BM,';')
boyer2 = '#f93a6e'

plt.plot(BM_t['m'], BM_t['hash'], color=boyer2, label='Hash table')
plt.plot(BM_t['m'], BM_t['array'], color=boyer, label='Array')

plt.ylabel('Tiempo [ms]')
plt.xlabel('Tamaño patron')
plt.title('Boyer Moore con distintos contenedores para la tabla')
plt.legend(loc='upper right')

plt.show()
