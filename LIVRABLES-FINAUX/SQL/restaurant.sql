CREATE TABLE IF NOT EXISTS "commandes" (
	"commande_id"	INTEGER,
	"employe_id"	INTEGER,
	"heure_commande"	DATETIME NOT NULL,
	"statut"	VARCHAR(50) NOT NULL,
	PRIMARY KEY("commande_id" AUTOINCREMENT),
	FOREIGN KEY("employe_id") REFERENCES "employes"("employe_id")
);
CREATE TABLE IF NOT EXISTS "employes" (
	"employe_id"	INTEGER,
	"nom"	TEXT NOT NULL,
	"role"	TEXT NOT NULL,
	"date_embauche"	DATE NOT NULL,
	PRIMARY KEY("employe_id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "ingredients" (
	"ingredient_id"	INTEGER,
	"nom"	TEXT NOT NULL,
	"type"	TEXT NOT NULL,
	"quantite"	INTEGER NOT NULL,
	"date_reception"	DATE,
	"date_peremption"	DATE,
	PRIMARY KEY("ingredient_id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "inventaire" (
	"inventaire_id"	INTEGER,
	"nom_item"	TEXT NOT NULL,
	"categorie"	TEXT NOT NULL,
	"quantite"	INTEGER NOT NULL,
	PRIMARY KEY("inventaire_id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "menu" (
	"menu_id"	INTEGER,
	"nom"	TEXT NOT NULL,
	"description"	TEXT,
	"prix"	REAL NOT NULL,
	"type_menu"	TEXT NOT NULL,
	PRIMARY KEY("menu_id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "taches" (
	"tache_id"	INTEGER,
	"employe_id"	INTEGER,
	"description"	TEXT NOT NULL,
	"statut"	TEXT NOT NULL,
	"heure_assignee"	DATETIME NOT NULL,
	"heure_completee"	DATETIME,
	PRIMARY KEY("tache_id" AUTOINCREMENT),
	FOREIGN KEY("employe_id") REFERENCES "employes"("employe_id")
);

