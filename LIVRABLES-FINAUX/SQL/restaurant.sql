
CREATE TABLE IF NOT EXISTS "commandes" (
	"id"	INTEGER,
	"client_id"	INTEGER NOT NULL,
	"table_id"	INTEGER NOT NULL,
	"dish_name"	TEXT NOT NULL,
	"quantity"	INTEGER NOT NULL,
	"created_at"	DATETIME DEFAULT CURRENT_TIMESTAMP,
	PRIMARY KEY("id" AUTOINCREMENT)
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
	"dish_name"	TEXT NOT NULL,
	"quantite"	INTEGER NOT NULL,
	"nom"	TEXT NOT NULL,
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
CREATE TABLE IF NOT EXISTS "orders" (
	"order_id"	INTEGER,
	"client_id"	INTEGER NOT NULL,
	"table_id"	INTEGER NOT NULL,
	"dish_name"	TEXT NOT NULL,
	"quantity"	INTEGER NOT NULL,
	PRIMARY KEY("order_id" AUTOINCREMENT)
);