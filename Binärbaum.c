#include <stdio.h>
#include <stdlib.h>

struct Knoten {
    int element;
    struct Knoten* links;
    struct Knoten* rechts;
};

int zaehler(struct Knoten*);
struct Knoten* erstelleKnoten(int);
struct Knoten* erstelleBinaerbaum(int);
void baumrest(int, int, struct Knoten*);

//Alle nach dem Wurzelelement folgenden linken und rechten Knoten werden gezaehlt
int zaehler(struct Knoten* t) {
    if (t == NULL) {
    return 0;
    }
    return 1 + zaehler(t->links) + zaehler(t->rechts);
}

//Erstellen eines Knoten
struct Knoten* erstelleKnoten(int element) {
    struct Knoten* t = malloc(sizeof(struct Knoten));
    t->element = element;
    t->links = t->rechts = NULL;
    printf("Knoten mit Element: %d wurde erzeugt\n", element);
    return t;
}

//Zusammensetzen des Binaerbaums
struct Knoten* erstelleBinaerbaum(int zaehlerKnoten) {
    struct Knoten* baum = malloc(sizeof(struct Knoten));
    baum = erstelleKnoten(1);
    baumrest(zaehlerKnoten, 1, baum);
    return baum;
}

//Baumrest wird erstellt (Baumrest = alle nachfolgende Elemente nach der Wurzel)
void baumrest(int nachf, int element, struct Knoten* baum) {
    int const kind_links  = 2*element;
    int const kind_rechts = 2*element+1; 
    printf("\n");
    printf("Aktuelles Element: %d\n", element);
    printf("->moegliches linkes Kind: %d\n",  kind_links);
    printf("->moegliches rechtes Kind: %d\n\n", kind_rechts);
    if (element > nachf) {
        return;
    }
    else {
        baum->element = element;
        //Überprüfen ob linkes Kind mit gewuenschter Anzahl an Knoten erstellt werden kann
        //Falls linkes Kind nicht erstellen werden kann, kann das rechte Kind auch nicht erstellt werden
        if (kind_links <= nachf) {
            baum->links  = erstelleKnoten(kind_links);
            baumrest(nachf, kind_links, baum->links);
        if (kind_rechts <= nachf) {
            baum->rechts = erstelleKnoten(kind_rechts);
            baumrest(nachf, kind_rechts, baum->rechts);
        }  
        }
    return;
    }
 }

//Ausgabefunktion Binaerbaum
void binaerbaum(struct Knoten* baum) {
    if (baum->links != NULL) {
        printf("(");
        binaerbaum(baum->links);
        printf(")<-");
    }
    //Blaetter werden mit ()-Klammern markiert, innere Knoten und Wurzel mit []-Klammern
    if (baum->links != NULL && baum->rechts != NULL) {
        printf("[%d]",baum->element);
    }
    else {
        printf("%d",baum->element);
    }
    if (baum->rechts != NULL) {
        printf("->(");
        binaerbaum(baum->rechts);
        printf(")");
    }
}

int main() {
    int zaehlerKnoten = 0;
    while (zaehlerKnoten<1) {
        printf("- - - Erstellungsprozess Binaerbaum - - - \n");
        printf("Aus wie vielen Knoten soll der Binaerbaum bestehen? ");
        scanf("%d", &zaehlerKnoten);
        printf("\n");
    }
    struct Knoten* Wurzel = erstelleBinaerbaum(zaehlerKnoten);
    printf("Erstellte Knoten: %d\n", zaehler(Wurzel));
    printf("- - - Erstellungsprozess beendet - - -\n\n");
    printf("- - - Fertiger Binaerbaum - - -\n");
    printf("Anmerkung: Blaetter werden mit ()-Klammern gekennzeichnet \n");
    printf("Anmerkung: Durchnummerierung erfolgt in Level-Order-Verfahren \n");
    binaerbaum(Wurzel);
    printf("\n");
} 