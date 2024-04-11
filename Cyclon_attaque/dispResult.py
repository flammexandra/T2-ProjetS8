import matplotlib.pyplot as plt

def lire_fichier(nom_fichier):
    valeurs = []
    with open(nom_fichier, 'r') as f:
        for ligne in f:
            try:
                valeur = float(ligne.strip())
                valeurs.append(valeur)
            except ValueError:
                pass  # Ignorer les lignes qui ne contiennent pas de valeurs numériques
    return valeurs

def tracer_courbes(liste_de_valeurs, noms_fichiers):
    for valeurs, nom_fichier in zip(liste_de_valeurs, noms_fichiers):
        plt.plot(valeurs, label=nom_fichier)
    plt.xlabel('Index de la ligne')
    plt.ylabel('Valeur')
    plt.title('Superposition des courbes des fichiers')
    plt.grid(True)
    plt.legend()
    plt.show()

if __name__ == "__main__":
    noms_fichiers = ["result_10000_3.txt", "result_10000_5.txt", "result_10000_8.txt","result_10000_10.txt"]  # Liste des noms de fichiers
    valeurs = [lire_fichier(nom) for nom in noms_fichiers]  # Lire les valeurs de chaque fichier
    tracer_courbes(valeurs, noms_fichiers)  # Tracer les courbes
