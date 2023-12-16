# Bonjour monsieur go!

je propose ces petites normes pour mieux nous retrouver dans le code
n'hesitez pas a rajouter des regles a ce document et a me dire si une
quelconque regle ne vous plait pas.

# Les noms de fonctions.

les mots dans un nom de fonction vont du plus generique au plus precis.
[type]_[action]([arguments])
ex: vec3_malloc
ex: vec3_swap_x_y
ex: vec3_malloc_err

ainsi chaque fonction qui ont un rapport avec un vecteur commencent par
vec3! :D

comme montre plus haut on peut raccourir `_error` en `_err` faisant
ainsi des *lignes plus courtes* un peu plus bas je tiens un liste des
abbreviations qu'on utilise dans le code

# les noms de variables

i j k sont toujours des unsigned int qui servent de maniere temporaire
pour incrementer quelque chose.

# abbreviations

err = error
