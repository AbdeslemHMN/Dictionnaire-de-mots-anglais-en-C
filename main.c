#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define NUM_LETTERS 26
#define Max_Letters 50
#define ESC 27

int Lists_PreffSuff = 0;
int Lists_Anag = 0;
int Lists_OneDiff = 0;
int Lists_ed = 0;
int Lists_ing = 0;
int Lists_ajout_graduel = 0;

typedef char string[50]; // le type chaine

typedef struct pastP {     // List of ed
    char past[Max_Letters];
    struct pastP* nextED;
}pastP;


typedef struct presentC {  // List of ing
    char present[Max_Letters];
    struct presentC* nextING;
}presentC;


typedef struct syllable {
    char Syllabe[Max_Letters];
    struct  syllable* NextSyl;
} syllable;


typedef struct anagram
{
    char anag[Max_Letters];
    struct anagram* next_anag;
} anagram;


typedef struct main_anag
{
    char main_word[Max_Letters];
    struct main_anag* next_main;
    anagram* anag_words;
} main_anag;


typedef struct mot {
    char word[Max_Letters];
    int length;
    int num_vowels;
    int num_consonants;
    int num_syllables;
    bool ordered;
    bool is_anagram;
    bool is_preff;
    bool is_onediff;
    struct mot* prec;
    struct mot* suiv;
    syllable* Syl;
} mot;

mot* lists[NUM_LETTERS] = {NULL};

void Textecolor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
// Texte couleur et fond:
void Color(int couleurdutexte, int couleurdufond)
{

    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurdufond * 16 + couleurdutexte);
}

// manipuler les cordonn�s de la console gotoxy :
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//********************************************Interface*********************************
//****************************************************************************************
void welcome()

{
    int k;
    system("Cls");
    for (k = 0; k < 10; k++)
    {
        if (k % 2 == 0)
            Textecolor(5);
        if (k % 2 == 1)
            Textecolor(3);
        printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t  .----------------.  .----------------.  .----------------.\n");
    printf("\t\t\t\t\t\t | .--------------. || .--------------. || .--------------. |\n");
    printf("\t\t\t\t\t\t | |  _________   | || |    _______   | || |     _____    | |\n");
    printf("\t\t\t\t\t\t | | |_   ___  |  | || |   /  ___  |  | || |    |_   _|   | |\n");
    printf("\t\t\t\t\t\t | |   | |_  \\_|  | || |  |  (__ \\_|  | || |      | |     | |\n");
    printf("\t\t\t\t\t\t | |   |  _|  _   | || |   \'.___`-.   | || |      | |     | |\n");
    printf("\t\t\t\t\t\t | |  _| |___/ |  | || |  |`\\____) |  | || |     _| |_    | |\n");
    printf("\t\t\t\t\t\t | | |_________|  | || |  |_______.\'  | || |    |_____|   | |\n");
    printf("\t\t\t\t\t\t | |              | || |              | || |              | |\n");
    printf("\t\t\t\t\t\t | \'--------------\' || \'--------------\' || \'--------------\' |\n");
    printf("\t\t\t\t\t\t  \'----------------\'  \'----------------\'  \'----------------\'\n");
    Sleep(200);
    system("cls");
    }
    Textecolor(5);
    printf("\t\t\t\t\t\t          R%cpublique Alg%crienne D%cmocratique et Populaire           \n", 130, 130, 130);
    printf("\t\t\t\t\t\tMinist%cre de l'Enseignement Sup%crieur et de la Recherche Scientifique\n\n\n", 130, 130);
    printf("\t\t\t\t\t\t     _______________________________________________________\n");
    printf("\t\t\t\t\t\t    |        _______     _______     _                      |\n");
    printf("\t\t\t\t\t\t    |       |  _____|   |  _____|   | |  %ccole nationale    |\n", 130);
    printf("\t\t\t\t\t\t    |       | |_____    | |_____    | |                     |\n");
    printf("\t\t\t\t\t\t    |       |  _____|   |_____  |   | |  sup%crieure         |\n", 130);
    printf("\t\t\t\t\t\t    |       | |_____     _____| |   | |                     |\n");
    printf("\t\t\t\t\t\t    |       |_______|   |_______|   |_|  d'informatique     |\n");
    printf("\t\t\t\t\t\t    |_______________________________________________________|\n\n\n");
    Textecolor(3);
    printf("\t\t\t\t\t\t\tCPI - 1%cre Ann%ce - Ann%ce Universitaire 2022/2023 \n\n\n", 138, 130, 130);
    printf("\t\t\t\t\t\t ___________________________________________________________________\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t| REALISE PAR :       MABROUKI ABDERRAHMANE                         |\n");
    printf("\t\t\t\t\t\t|                              &                                    |\n");
    printf("\t\t\t\t\t\t|                       HAMMANI ABDESLEM                            |\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t|           SECTION : A           GROUPE: 03                        |\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t|           TP1 :        Linked Lists                               |\n", 130, 130);
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t|                   < English Dictionary >                          |\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t|                                                                   |\n");
    printf("\t\t\t\t\t\t| Supervised By :Mrs. Artabaz Saliha                                |\n");
    printf("\t\t\t\t\t\t|___________________________________________________________________|\n\n\n");
    Sleep(200);
    Sleep(200);
    Textecolor(5);
    printf("\n");
    printf("\t\t\t\t\t\t                             PLease                                         \n");
    printf("\t\t\t\t\t\t                    Press any key to continue..                             ");
    getch();
}
// charrgement affichage:
void Chargement()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        system("cls");
        Textecolor(4);
        gotoxy(12, 17);
        printf("\t\t\t\t\t\t\t\t  Loading.\n\n");
        Sleep(200);
        system(";cls");
        gotoxy(12, 17);
        printf("\t\t\t\t\t\t\t\t  Loading..\n\n");
        Sleep(200);
        system(";cls");
        gotoxy(12, 17);
        printf("\t\t\t\t\t\t\t\t  Loading...\n\n");
        Sleep(200);
        system(";cls");
    }
}
// barre du chargement:

void Barrechargement()
{
    system("cls");
    Textecolor(4);
    gotoxy(10, 15);
    printf("\t\t\t\t\t|||                                                 5%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t|||||                                               20%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t||||||||||||||||                                    30%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t|||||||||||||||||||||||||                           45%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t|||||||||||||||||||||||||||||||                     60%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t||||||||||||||||||||||||||||||||||||||||            80%%  ");
    Sleep(300);
    system(";cls");
    gotoxy(10, 15);
    printf("\t\t\t\t\t||||||||||||||||||||||||||||||||||||||||||||||||||  100%% ");
    system("cls");
}

// openign interface 2:
void Welcome2()
{
    system("cls");
    for (int k = 0; k < 10; k++)
    {
        if (k % 2 == 0)
            Textecolor(5);
        if (k % 2 == 1)
            Textecolor(3);
printf("\n\n\n\n\n\n\n");
printf("\t\t\t\t\t\t  .----------------.  .----------------.  .----------------. \n");
printf("\t\t\t\t\t\t | .--------------. || .--------------. || .--------------. |\n");
printf("\t\t\t\t\t\t | |  _________   | || |   ________   | || |     __       | |\n");
printf("\t\t\t\t\t\t | | |  _   _  |  | || |  |_   __  |  | || |    /  |      | |\n");
printf("\t\t\t\t\t\t | | |_| | | |_|  | || |    | |__) |  | || |    `| |      | |\n");
printf("\t\t\t\t\t\t | |     | |      | || |    |  ___/   | || |     | |      | |\n");
printf("\t\t\t\t\t\t | |    _| |_     | || |   _| |_      | || |    _| |_     | |\n");
printf("\t\t\t\t\t\t | |   |_____|    | || |  |_____|     | || |   |_____|    | |\n");
printf("\t\t\t\t\t\t | |              | || |              | || |              | |\n");
printf("\t\t\t\t\t\t | '--------------' || '--------------' || '--------------' |\n");
printf("\t\t\t\t\t\t '----------------'  '----------------'  '----------------' \n\n\n\n");
printf("\t\t\t\t\t\t .----------------.  .----------------.  .----------------.  \n");
printf("\t\t\t\t\t\t | .--------------. || .--------------. || .--------------. |\n");
printf("\t\t\t\t\t\t | |   _____      | || |   _____      | || |     ______   | |\n");
printf("\t\t\t\t\t\t | |  |_   _|     | || |  |_   _|     | || |   .' ___  |  | |\n");
printf("\t\t\t\t\t\t | |    | |       | || |    | |       | || |  / .'   |_|  | |\n");
printf("\t\t\t\t\t\t | |    | |   _   | || |    | |   _   | || |  | |         | |\n");
printf("\t\t\t\t\t\t | |   _| |__/ |  | || |   _| |__/ |  | || |  | `.___.'|  | |\n");
printf("\t\t\t\t\t\t | |  |________|  | || |  |________|  | || |   `._____.'  | |\n");
printf("\t\t\t\t\t\t | |              | || |              | || |              | |\n");
printf("\t\t\t\t\t\t | '--------------' || '--------------' || '--------------' |\n");
printf("\t\t\t\t\t\t '----------------'  '----------------'  '----------------'  \n");
Sleep(200);
system("cls");
}
    system("cls");
}

void GoodBye(){
system("cls");
printf("\n\n\n\n\n\n\n");
printf("\t\t\t\t .----------------.  .----------------.  .----------------.  .-----------------. .----------------. \n");
printf("\t\t\t\t| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
printf("\t\t\t\t| |  _________   | || |  ____  ____  | || |      __      | || | ____  _____  | || |  ___  ____   | |\n");
printf("\t\t\t\t| | |  _   _  |  | || | |_   ||   _| | || |     /  |     | || ||_   ||_   _| | || | |_  ||_  _|  | |\n");
printf("\t\t\t\t| | |_/ | | |_|  | || |   | |__| |   | || |    / /| |    | || |  |   ( | |   | || |   | |_/ /    | |\n");
printf("\t\t\t\t| |     | |      | || |   |  __  |   | || |   / ____ |   | || |  | |( (| |   | || |   |  __'.    | |\n");
printf("\t\t\t\t| |    _| |_     | || |  _| |  | |_  | || | _/ /    | |_ | || | _| |_(   |_  | || |  _| |  | |_  | |\n");
printf("\t\t\t\t| |   |_____|    | || | |____||____| | || ||____|  |____|| || ||_____|(____| | || | |____||____| | |\n");
printf("\t\t\t\t| |              | || |              | || |              | || |              | || |              | |\n");
printf("\t\t\t\t| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
printf("\t\t\t\t '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n\n\n");
printf("\t\t\t\t           .----------------.  .----------------.  .----------------.  .----------------. \n");
printf("\t\t\t\t          | .--------------. || .--------------. || .--------------. || .--------------. |\n");
printf("\t\t\t\t          | |  ____  ____  | || |     ____     | || | _____  _____ | || |              | |\n");
printf("\t\t\t\t          | | |_  _||_  _| | || |   .'    `.   | || ||_   _||_   _|| || |      _       | |\n");
printf("\t\t\t\t          | |   ( |  / /   | || |  /  .--.  |  | || |  | |    | |  | || |     | |      | |\n");
printf("\t\t\t\t          | |    ( |/ /    | || |  | |    | |  | || |  | '    ' |  | || |     | |      | |\n");
printf("\t\t\t\t          | |    _|  |_    | || |  |  `--'  /  | || |   | `--' /   | || |     | |      | |\n");
printf("\t\t\t\t          | |   |______|   | || |   `.____.'   | || |    `.__.'    | || |     |_|      | |\n");
printf("\t\t\t\t          | |              | || |              | || |              | || |     (_)      | |\n");
printf("\t\t\t\t          | '--------------' || '--------------' || '--------------' || '--------------' | \n");
printf("\t\t\t\t           '----------------'  '----------------'  '----------------'  '----------------' \n");
Sleep(2200);
system("cls");
}

/***********************************************************/
/**** Impl�mentation de la machine abstraite LLCs de TP ****/
/****               Par: Mabrouki/Hammani               ****/
/***********************************************************/


// On alloue dynamiquement la structure de contr�le avec un malloc.
// La taille � allouer est calcul�e automatiquement avec  sizeof (mot).
// L'ordinateur saura qu'il doit allouer l'espace n�cessaire au stockage de la structure mot.

void Allouer_Syllabe(syllable* p)
{
    p = (syllable*)malloc(sizeof(syllable));
}

// Proc�dure qui d�truit le mot point� par p.
void Liberer_Syllabe (syllable* p)
{
    free(p);
}

// Proc�dure qui affecte q dans le champ (NextSyl) du mot point� par p.
void Aff_adr_suivsyl(syllable* p, syllable* q)
{
    p->NextSyl = q;     // (p->NextSyl) est l'�quivalent de (*p.NextSyl)
}

// Proc�dure qui affecte q dans le champ (Syl) du mot point� par p.
void Aff_syl(syllable* p, char* v)
{
    strcpy(p->Syllabe, v);     // (p->NextSyl) est l'�quivalent de (*p.NextSyl)
}

// Fonction qui retourne le contenu du champ (Syl) du mot point� par p.
char* Syllabe(syllable* p)
{
    return p->Syllabe;     // (p->NextSyl) est l'�quivalent de (*p.NextSyl)
}

// Fonction qui retourne le contenu du champ (Syl) du mot point� par p.
syllable* NextSyl(syllable* p)
{
    return p->NextSyl;     // (p->NextSyl) est l'�quivalent de (*p.NextSyl)
}

void Allouer_mot(mot** p)
{
    *p = (mot*)malloc(sizeof(mot));
}

// Proc�dure qui d�truit le mot point� par p.
void Liberer_mot (mot* p)
{
    free(p);
}

// Proc�dure qui affecte v dans le champ (val)du mot point� par p.
void Aff_mot(mot* p, char* v)
{
    strcpy(p->word, v);    // (p->val) est l'�quivalent de (*p.val)
}

// Proc�dure qui affecte v dans le champ (length)du mot point� par p.
void Aff_length(mot* p, int v)
{
    p->length = v;     // (p->val) est l'�quivalent de (*p.val)
}

// Proc�dure qui affecte v dans le champ (num_vowels)du mot point� par p.
void Aff_num_vowels(mot* p, int v)
{
    p->num_vowels = v;     // (p->val) est l'�quivalent de (*p.val)
}

// Proc�dure qui affecte v dans le champ (num_consonants)du mot point� par p.
void Aff_num_consonants(mot* p, int v)
{
    p->num_consonants = v;     // (p->val) est l'�quivalent de (*p.val)
}

// Proc�dure qui affecte v dans le champ (num_syylables)du mot point� par p.
void Aff_num_Syllables(mot* p, int v)
{
    p->num_syllables = v;     // (p->val) est l'�quivalent de (*p.val)
}

// Proc�dure qui affecte q dans le champ (suivant) du mot point� par p.
void Aff_adr_suiv(mot* p, mot* q)
{
    p->suiv = q;     // (p->adr) est l'�quivalent de (*p.adr)
}

// Proc�dure qui affecte q dans le champ (precedent) du mot point� par p.
void Aff_adr_prec(mot* p, mot* q)
{
    p->prec = q;     // (p->adr) est l'�quivalent de (*p.adr)
}

// Proc�dure qui affecte q dans le champ (precedent) du mot point� par p.
void Aff_adr_Syl(mot* p, syllable* q)
{
    p->Syl = q;     // (p->adr) est l'�quivalent de (*p.adr)
}

// Proc�dure qui affecte q dans le champ (ordered) du mot point� par p.
void Aff_ordered(mot* p, bool q)
{
    p->ordered = q;     // (p->adr) est l'�quivalent de (*p.adr)
}


// Fonction qui retourne le contenu du champ (Word) du mot point� par p.
char* Word (mot* p)
{
    return p->word;
}

// Fonction qui retourne le contenu du champ (suiv) du mot point� par p.
mot* Suivant (mot* p)
{
    return p->suiv;
}

// Fonction qui retourne le contenu du champ (prec) du mot point� par p.
mot* Prec (mot* p)
{
    return p->prec;
}

// Fonction qui retourne le contenu du champ (Length) du mot point� par p.
int Length (mot* p)
{
    return p->length;
}

// Fonction qui retourne le contenu du champ (Num_vowels) du mot point� par p.
int Num_Vowels (mot* p)
{
    return p->num_vowels;
}

// Fonction qui retourne le contenu du champ (Num_consonants) du mot point� par p.
int Num_Consonants (mot* p)
{
    return p->num_consonants;
}

// Fonction qui retourne le contenu du champ (Num_syllables) du mot point� par p.
int Num_Syllables (mot* p)
{
    return p->num_syllables;
}

// Fonction qui retourne le contenu du champ (ordered) du mot point� par p.
bool Ordered (mot* p)
{
    return p->ordered;
}

// Fonction qui retourne le contenu du champ (Syll) du mot point� par p.
syllable* Syl(mot* p)
{
    return p->Syl;
}

char* remove_slash(char* str) {
    int i, j;
    int n = strlen(str);
    char* new_str = malloc(n + 1); // Allocate memory for new string

    for (i = 0, j = 0; i < n; i++) {
        if (str[i] != '/' && str[i] != '\n' && str[i] != ' ') {
            new_str[j++] = tolower(str[i]); // Copy non-slash characters to new string
        }
    }
    new_str[j] = '\0'; // Add null terminator at the end of the new string
    return new_str;
}

// Fonction qui calcule le nombre de voyelles dans un mot
int count_vowels(char* word) {
    int count = 0;
    for (int i = 0; i < strlen(word); i++) {
        char c = word[i];
        if (toupper(c) == 'A' || toupper(c)== 'I' || toupper(c)== 'E' || toupper(c) == 'O' || toupper(c) == 'U' || toupper(c)== 'Y') {
            count++;
        }
    }
    return count;
}

// Fonction qui calcule le nombre de consonnes dans un mot
int count_consonants(char* word) {
    int count = 0;
    for (int i = 0; i < strlen(word); i++) {
        char c = word[i];
        if (toupper(c) >= 'A' && toupper(c) <= 'Z' && !count_vowels(&c)) {
            count++;
        }
    }
    return count;
}

// Fonction qui calcule le nombre de syllabes dans un mot
int count_syllables(char* word) {
    int count = 1;
    for (int i = 0; i < strlen(word); i++) {
        char c = word[i];
        if (c == '/') {
            count++;
        }
    }
    // On ajoute 1 car il y a toujours une syllabe de plus que le nombre de / dans le mot
    return count;
}

// Fonction qui v�rifie si le mot est form� d'une s�quence de lettres selon l'ordre alphab�tique
bool is_ordered(char* word) {
    for (int i = 1; i < strlen(word) ; i++) {
        char c1 = toupper(word[i-1]);
        char c2 = toupper(word[i]);
        if (c1 > c2) {
            return false;
        }
    }
    return true;
}


void order_word(char* word) {
    for (int i = 0; i < strlen(word)-1; i++) {
        for (int j = i+1; j < strlen(word); j++) {
            char c1 = word[i];
            char c2 = word[j];
            if (toupper(c1) > toupper(c2)) {
                // On �change les deux caract�res
                word[i] = c2;
                word[j] = c1;
            }
        }
    }
}

mot* createnewnode(char* word) {
    mot* temp = malloc(sizeof(mot));
    temp->is_anagram = false;
    temp->is_preff = false;
    temp->is_onediff = false;
    char* new_word = remove_slash(word);
    Aff_mot(temp,new_word);
    Aff_length(temp,strlen(new_word));
    Aff_num_vowels(temp, count_vowels(new_word));
    Aff_num_consonants(temp, count_consonants(new_word));
    Aff_num_Syllables(temp, count_syllables(word));
    Aff_ordered(temp, is_ordered(new_word));
    Aff_adr_prec(temp,NULL);
    Aff_adr_suiv(temp,NULL);
    Aff_adr_Syl (temp, NULL);
    free(new_word);
    return temp;
}


void print_list_syl(syllable* head)
{
    if (head == NULL) {
        printf("The List is empty\n");
        return;
    }
    syllable* temp = head;
    while (temp != NULL)
    {
        printf("%s ", Syllabe(temp));
        temp = NextSyl(temp);
    }
    printf("\n");
}

void print_list_mot(mot* head) {

    while (head != NULL) {
        char temp[50];
        bool order = false;
        strcpy(temp, Word(head));
        printf("\n");
        printf(" ---------------\n");
        printf("|               |\n");
        printf("    %s\n", Word(head));
        printf("|               |\n");
        printf(" ---------------\n\n");
        printf("Number Of Caracters : %d\n", Length(head));
        printf("Number Of Vowels : %d\n", Num_Vowels(head));
        printf("Number Of Consonants : %d\n", Num_Consonants(head));
        printf("Number Of Syllables : %d\n", Num_Syllables(head));
        printf("The Word is Ordered Alphabetically : %s\n", Ordered(head) ? "Yes" : "No");
        // Si le mot n'est pas ordonn�,
        if (!Ordered(head)) {
            order_word(temp);
        }
        printf("The Ordered Word is : %s\n", temp);
        printf("The Syllables Of The Word '%s' Are: ",Word(head));
        print_list_syl(Syl(head));
        printf("\n\n");
        head = Suivant(head);
    }
}

pastP* new_pastP(char* word){
    pastP* temp = malloc(sizeof(pastP));
    temp->nextED = NULL;
    strcpy(temp->past, word);
    return temp;
}

presentC* new_presentC(char* word){
    presentC* temp = malloc(sizeof(presentC));
    temp->nextING = NULL;
    strcpy(temp->present, word);
    return temp;
}


void insert_ed(pastP** head, char* word){

    word = remove_slash(word);
    if (word[strlen(word)-2] == 'e' && word[strlen(word)-1] == 'd')
    {
        pastP* temp1 = new_pastP(word);
        if (*head == NULL)
        {
            *head = temp1;
            return;
        }
        pastP* temp = *head;
        while (temp->nextED != NULL)
        {
            temp = temp->nextED;
        }
        temp->nextED = temp1;
        return;
    }
    free(word);
    return;
}

void insert_ing(presentC** head, char* word){

    word = remove_slash(word);
    if (word[strlen(word)-1] == 'g' && word[strlen(word)-2] == 'n' && word[strlen(word)-3] == 'i')
    {
        presentC* temp1 = new_presentC(word);
        if (*head == NULL)
        {
            *head = temp1;
            return;
        }
        presentC* temp = *head;
        while (temp->nextING != NULL)
        {
            temp = temp->nextING;
        }
        temp->nextING = temp1;
    }
    free(word);
    return;
}

void print_list_ed(pastP* head)
{
    printf("\n\n");
    if (head == NULL) {
        printf("\n\n");
        printf("                        There Are No Words in The Past Participle!\n");
        return;
    }
    pastP* temp = head;
    printf("   The words that are in the past participle are: \n\n");
    while (temp != NULL)
    {
        printf("    -------------\n");
        printf("   |             |\n");
        printf("      %s\n", temp->past);
        printf("   |             |\n");
        printf("    -------------\n");
        temp = temp->nextED;
    }
}

void print_list_ing(presentC* head)
{
    printf("\n\n");
    if (head == NULL) {
        printf("\n\n");
        printf("   There Are No Words That End With 'ing'!\n");
        return;
    }
    presentC* temp = head;
    printf("   The Words That End With 'ing' Are: \n\n");
    while (temp != NULL)
    {
        printf("    -------------\n");
        printf("   |             |\n");
        printf("      %s\n", temp->present);
        printf("   |             |\n");
        printf("    -------------\n");
        temp = temp->nextING;
    }
}

void free_list(mot* head) {
    mot* current = head;
    while (current != NULL) {
        mot *suiv = Suivant(current);
        free(Word(current));
        free(current);
        current = suiv;
    }
}

void free_Syllable(syllable* head){
    syllable* current = head;
    while (current != NULL){
        syllable* suiv = NextSyl(current);
        free(current);
        current = suiv;
    }
}

syllable* new_syllabe(char* word)
{
    syllable* temp = malloc(sizeof(syllable));
    Aff_adr_suivsyl(temp, NULL);
    Aff_syl(temp, strcpy(temp->Syllabe,word));

    return temp;
}

void insert_syllables(syllable** head, char* word)
{
    char* token;
    token = strtok(word, "/");

    while (token != NULL) {
        syllable* temp = new_syllabe(token);
        if (*head == NULL) {
            *head = temp;
        }
        else {
            syllable* temp1 = *head;
            while(NextSyl(temp1) != NULL) {
                temp1 = NextSyl(temp1);
            }
            Aff_adr_suivsyl(temp1, temp);
        }
        token = strtok(NULL, "/");
    }

}

void insertmot(mot** head_ref, char* word)
{
    mot* temp = createnewnode(word);
    insert_syllables(&(temp->Syl), word);
    if (*head_ref == NULL)
    {
        *head_ref = temp;
        return;
    }

    mot* current = *head_ref;
    while (current != NULL) {
        if (Length(temp) < Length(current)) {
            Aff_adr_suiv(temp, current);
            Aff_adr_prec(temp, Prec(current));
            if (Prec(current) != NULL) {
                Aff_adr_suiv(Prec(current), temp);
            } else {
                *head_ref = temp;
            }
            Aff_adr_prec(current, temp);
            return;
        } else if (Length(temp) == Length(current)) {
            int cmp = strcmp(temp->word, current->word);
            if (cmp < 0 || (cmp == 0 && Word(temp) < Word(current))) {
                Aff_adr_suiv(temp, current);
                Aff_adr_prec((temp), Prec(current));
                if (Prec(current) != NULL) {
                    Aff_adr_suiv(Prec(current), temp);
                } else {
                    *head_ref = temp;
                }
                Aff_adr_prec(current, temp);
                return;
            }
        }
        if (Suivant(current) == NULL) {
            Aff_adr_suiv(current, temp);
            Aff_adr_prec(temp, current);
            return;
        }
        current = Suivant(current);
    }
}

void delete_mot(mot* head[]) {

    gotoxy(57, 10);
    printf("Enter a Word that You Want To Delete: ");
    char* word = malloc(50);
    scanf("%s",word);
    word = remove_slash(word);
    printf("\n");
    int index = tolower(word[0]) - 'a';
    mot* temp = head[index];
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            if (temp == head[index]) {  // node to be deleted is the head
                head[index] = temp->suiv;
                if (head[index] != NULL) {
                    (head[index])->prec = NULL;
                }
            } else if (temp->suiv == NULL) {  // node to be deleted is the tail
                temp->prec->suiv = NULL;
            } else {  // node to be deleted is in the middle of the list
                temp->prec->suiv = temp->suiv;
                temp->suiv->prec = temp->prec;
            }
            free_Syllable(temp->Syl);
            free(temp);
            free(word);
            gotoxy(57, 12);
            printf("The Word Was Deleted Successfully!");
            return;
        }
        temp = temp->suiv;
    }
    free(word);
    gotoxy(57, 12);
    printf("The Word Doesn't Exist!\n");
}

void print_words(mot* table[]){

    for (int i = 0; i < NUM_LETTERS; i++) {
        printf("-----------------------------------------------------------\n\n");
        if (table[i] == NULL)
    {
        printf("There Are No Words That Start With The Letter '%c'!\n\n", i + 'A');
        continue;
    }
        printf("The Words That Start With The Letter '%c' Are: ", i + 'A');
        print_list_mot(table[i]);
    }
}

void count_ed(pastP** head){
    if (*head != NULL)
    {
        if (Lists_ed == 0)
        {
            Lists_ed++;
            return;
        }
    }
    return;
}

void count_ing(presentC** head){
    if (*head != NULL)
    {
        if (Lists_ing == 0)
        {
            Lists_ing++;
            return;
        }
    }
    return;
}

void insert_word(mot* table[], presentC** head1, pastP** head2){
    char word[50];
    gotoxy(45, 10);
    printf("Enter a word where its syllables are separated by '/': ");
    scanf("%s", word);
    int ind = tolower(word[0])-'a';
    insertmot(&(table[ind]) , word);
    insert_ing(head1, word);
    insert_ed(head2, word);
    count_ed(head2);
    count_ing(head1);
    gotoxy(57, 12);
    printf("The Word Was Added Successfully!");
}

bool is_one_letter_diff(char* word1, char* word2) {
    if (strlen(word1) != strlen(word2)) {
        return false;
    }
    int diff_count = 0;
    for (int i = 0; i < strlen(word1); i++) {
        if (word1[i] != word2[i]) {
            diff_count++;
        }
        if (diff_count > 1) {
            return false;
        }
    }
    return diff_count == 1;
}


main_anag* new_main_anagr(char* word)
{
    main_anag* temp = malloc(sizeof(main_anag));
    temp->anag_words = NULL;
    temp->next_main = NULL;
    strcpy(temp->main_word, word);
    return temp;
}

anagram* new_anagram(char* word)
{
    anagram* temp = malloc(sizeof(anagram));
    temp->next_anag = NULL;
    strcpy(temp->anag, word);
    return temp;
}

void insert_main_anagram(main_anag** head,char* word)
{
    main_anag* temp1 = new_main_anagr(word);
    if (*head == NULL)
    {
        *head = temp1;
        return;
    }
    main_anag* temp2 = *head;
    while (temp2->next_main != NULL)
    {
        temp2 = temp2->next_main;
    }
    temp2->next_main = temp1;
}

void insert_anagram(anagram** head,char* word)
{
    anagram* temp1 = new_anagram(word);
    if (*head == NULL)
    {
        *head = temp1;
        return;
    }
    anagram* temp2 = *head;
    while (temp2->next_anag != NULL)
    {
        temp2 = temp2->next_anag;
    }
    temp2->next_anag = temp1;
}

void Fill_Anagrams(mot* table[], main_anag** head1)
{
    for (int i = 0; i < 26; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        mot* temp1 = table[i];
        while (temp1 != NULL)
        {
            char word1[50];
            strcpy(word1, Word(temp1));
            order_word(word1);
            if (temp1->is_anagram)
            {
                temp1 = Suivant(temp1);
                continue;
            }
            main_anag* current = *head1;
            main_anag* previous = NULL;
            bool found = false;
            while (current != NULL) {
                if (strcmp(current->main_word, word1) == 0) {
                    found = true;
                    break;
                }
                previous = current;
                current = current->next_main;
            }
            if (found) {
                // Word is already a main_anag, skip to the next word
                temp1 = Suivant(temp1);
                continue;
            }
            bool has_anagram = false;
            for (int j = 0; j < 26; j++)
            {
                if (table[j] == NULL)
                {
                    continue;
                }
                mot* temp2 = table[j];
                while (temp2 != NULL)
                {
                    char word2[50];
                    strcpy(word2, Word(temp2));
                    order_word(word2);
                    if (strcmp(word1, word2) == 0 && temp1 != temp2)
                    {
                        if (!has_anagram) {
                            // Create a new main_anag structure for word1
                            insert_main_anagram(head1, Word(temp1));
                            Lists_Anag++;
                            current = *head1;
                            while (current->next_main != NULL) {
                                current = current->next_main;
                            }
                            has_anagram = true;
                        }
                        found = false;
                        anagram* current_close = current->anag_words;
                        while (current_close != NULL) {
                            if (strcmp(current_close->anag, word2) == 0) {
                                found = true;
                                break;
                            }
                            current_close = current_close->next_anag;
                        }
                        if (!found) {
                            insert_anagram(&(current->anag_words), Word(temp2));
                            temp2->is_anagram = true;
                        }
                    }
                    temp2 = Suivant(temp2);
                }
            }

            temp1 = Suivant(temp1);
        }
    }
}

bool isFormedFromMain(char* formedWord, char* prefix) {
    int i = 0;
    int j = 0;
    while (formedWord[i] != '\0' && prefix[j] != '\0') {
        if (formedWord[i] == prefix[j]) {
            j++;
        }
        i++;
    }
    return prefix[j] == '\0';
}

void Fill_pref_suff(mot* table[], main_anag** head1)
{
    for (int i = 0; i < 26; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        mot* temp1 = table[i];
        while (temp1 != NULL)
        {
            char word1[50];
            strcpy(word1, Word(temp1));
            main_anag* current = *head1;
            main_anag* previous = NULL;
            bool found = false;
            while (current != NULL) {
                if (strcmp(current->main_word, word1) == 0) {
                    found = true;
                    break;
                }
                previous = current;
                current = current->next_main;
            }
            if (found) {
                // Word is already a main_anag, skip to the next word
                temp1 = Suivant(temp1);
                continue;
            }
            bool has_anagram = false;
            for (int j = 0; j < 26; j++)
            {
                if (table[j] == NULL)
                {
                    continue;
                }
                mot* temp2 = table[j];
                while (temp2 != NULL)
                {
                    char word2[50];
                    strcpy(word2, Word(temp2));
                    if (isFormedFromMain(word2, word1) && temp1 != temp2)
                    {
                        if (!has_anagram) {
                            // Create a new main_anag structure for word1
                            insert_main_anagram(head1, Word(temp1));
                            Lists_PreffSuff++;
                            current = *head1;
                            while (current->next_main != NULL) {
                                current = current->next_main;
                            }
                            has_anagram = true;
                        }
                        found = false;
                        anagram* current_close = current->anag_words;
                        while (current_close != NULL) {
                            if (strcmp(current_close->anag, word2) == 0) {
                                found = true;
                                break;
                            }
                            current_close = current_close->next_anag;
                        }
                        if (!found) {
                            insert_anagram(&(current->anag_words), Word(temp2));
                        }
                    }
                    temp2 = Suivant(temp2);
                }
            }

            temp1 = Suivant(temp1);
        }
    }
}

int countWords(mot* array[]) {
    int totalCount = 0;   // Compteur total de mots

    for (int i = 0; i < NUM_LETTERS; i++) {   // Parcourir tous les �l�ments du tableau
        mot* current = array[i];       // Pointeur vers le n�ud courant
        if (current == NULL)
        {
           continue;
        }
        while (current != NULL) {              // Parcourir la liste cha�n�e de chaque �l�ment
            totalCount++;                      // Incr�menter le compteur total
            current = current->suiv;            // Passer au prochain n�ud
        }
    }

    return totalCount;    // Retourner le nombre total de mots
}


void Fill_one_diff(mot* table[], main_anag** head1)
{
    for (int i = 0; i < 26; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        mot* temp1 = table[i];
        while (temp1 != NULL)
        {
            char word1[50];
            strcpy(word1, Word(temp1));
            if (temp1->is_onediff)
            {
                temp1 = Suivant(temp1);
                continue;
            }
            main_anag* current = *head1;
            main_anag* previous = NULL;
            bool found = false;
            while (current != NULL) {
                if (strcmp(current->main_word, word1) == 0) {
                    found = true;
                    break;
                }
                previous = current;
                current = current->next_main;
            }
            if (found) {
                // Word is already a main_anag, skip to the next word
                temp1 = Suivant(temp1);
                continue;
            }
            bool has_anagram = false;
            for (int j = 0; j < 26; j++)
            {
                if (table[j] == NULL)
                {
                    continue;
                }
                mot* temp2 = table[j];
                while (temp2 != NULL)
                {
                    char word2[50];
                    strcpy(word2, Word(temp2));
                    if (is_one_letter_diff(word1, word2) && temp1 != temp2)
                    {
                        if (!has_anagram) {
                            // Create a new main_anag structure for word1
                            insert_main_anagram(head1, Word(temp1));
                            Lists_OneDiff++;
                            current = *head1;
                            while (current->next_main != NULL) {
                                current = current->next_main;
                            }
                            has_anagram = true;
                        }
                        found = false;
                        anagram* current_close = current->anag_words;
                        while (current_close != NULL) {
                            if (strcmp(current_close->anag, word2) == 0) {
                                found = true;
                                break;
                            }
                            current_close = current_close->next_anag;
                        }
                        if (!found) {
                            insert_anagram(&(current->anag_words), Word(temp2));
                            temp2->is_onediff = true;
                        }
                    }
                    temp2 = Suivant(temp2);
                }
            }

            temp1 = Suivant(temp1);
        }
    }
}

bool isFormedGradually(char* word1, char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int diff = len1 - len2;

    if (diff == -1) {
        int i = 0, j = 0;
        while (i < len1 && j < len2) {
            if (word1[i] != word2[j]) {
                j++;
                if (j - i > 1) {
                    return false;
                }
            } else {
                i++;
                j++;
            }
        }
        return true;

    } else {
        return false;
    }
}

void Fill_ajout_graduel(mot* table[], main_anag** head1)
{
    for (int i = 0; i < 26; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        mot* temp1 = table[i];
        while (temp1 != NULL)
        {
            char word1[50];
            strcpy(word1, Word(temp1));
            char temp[50];
            strcpy(temp,word1);
            main_anag* current = *head1;
            main_anag* previous = NULL;
            bool found = false;
            while (current != NULL) {
                if (strcmp(current->main_word, word1) == 0) {
                    found = true;
                    break;
                }
                previous = current;
                current = current->next_main;
            }
            if (found) {
                // Word is already a main_anag, skip to the next word
                temp1 = Suivant(temp1);
                continue;
            }
            bool has_anagram = false;
            for (int j = 0; j < 26; j++)
            {
                if (table[j] == NULL)
                {
                    continue;
                }
                mot* temp2 = table[j];
                while (temp2 != NULL)
                {
                    char word2[50];
                    strcpy(word2, Word(temp2));
                    if (isFormedGradually(temp, word2) && temp1 != temp2)
                    {
                        if (!has_anagram) {
                            // Create a new main_anag structure for word1
                            insert_main_anagram(head1, Word(temp1));
                            Lists_ajout_graduel++;
                            current = *head1;
                            while (current->next_main != NULL) {
                                current = current->next_main;
                            }
                            has_anagram = true;
                        }
                        found = false;
                        anagram* current_close = current->anag_words;
                        while (current_close != NULL) {
                            if (strcmp(current_close->anag, word2) == 0) {
                                found = true;
                                break;
                            }
                            current_close = current_close->next_anag;
                        }
                        if (!found) {
                            insert_anagram(&(current->anag_words), Word(temp2));
                            strcpy(temp, Word(temp2));
                        }
                    }
                    temp2 = Suivant(temp2);
                }
            }

            temp1 = Suivant(temp1);
        }
    }
}


void print_ListAnagram(main_anag* head) {
    main_anag* current = head;
    while (current != NULL) {
        printf(" -------------\n");
        printf("|             |\n");
        printf("     %s        \n", current->main_word);
        printf("|             |\n");
        printf(" -------------------------> ");
        anagram* current_close = current->anag_words;
        while (current_close != NULL) {
            printf("%s   ", current_close->anag);
            current_close = current_close->next_anag;
        }
        printf("\n\n");
        current = current->next_main;
    }
    printf("\n\n");
}


void free_list_anag(main_anag* head) {
    main_anag* current_main = head;
    while (current_main != NULL) {
        anagram* current_anag = current_main->anag_words;
        while (current_anag != NULL) {
            anagram* temp_anag = current_anag;
            current_anag = current_anag->next_anag;
            free(temp_anag);
        }
        main_anag* temp_main = current_main;
        current_main = current_main->next_main;
        free(temp_main);
    }
    head = NULL;
}

void free_list_ed(pastP* head) {
    pastP* current = head;
    while (current != NULL) {
        pastP* temp = current;
        current = current->nextED;
        free(temp);
    }
}

void free_list_ing(presentC* head) {
    presentC* current = head;
    while (current != NULL) {
        presentC* temp = current;
        current = current->nextING;
        free(temp);
    }
}

void free_table(mot* table[]) {
    for (int i = 0; i < 26; i++) {
        mot* current = table[i];
        while (current != NULL) {
            syllable* current_syl = current->Syl;
            while (current_syl != NULL) {
                syllable* temp_syl = current_syl;
                current_syl = current_syl->NextSyl;
                free(temp_syl);
            }
            mot* temp_mot = current;
            current = current->suiv;
            free(temp_mot);
        }
    }
}

void Maximize(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t ___________________________________________________________________________\n");
    printf("\t\t\t\t\t| ATTENTION PLEASE!                                                         |\n");
    printf("\t\t\t\t\t|                                                                           |\n");
    printf("\t\t\t\t\t|                  Please Maximize Your Terminal Window !!                  |\n");
    printf("\t\t\t\t\t|                                                                           |\n");
    printf("\t\t\t\t\t|___________________________________________________________________________|\n");
    Sleep(5000);
}

void Read_File( mot* lists[NUM_LETTERS], pastP** List_ed, presentC** List_ing ){

    char name[50];
    system("cls");
    gotoxy(60, 10);
    printf("Enter the name of the file: ");
    gotoxy(65, 12);
    printf(" _____________");
    gotoxy(65, 13);
    printf("|             |");
    gotoxy(65, 14);
    printf("|             |");
    gotoxy(65, 15);
    printf("|_____________|\n");
    gotoxy(67, 14);
    scanf("%s",name);
    Chargement();
    printf("\n");
    FILE* file = fopen(name, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }
    char word[Max_Letters];
     while (fgets(word, sizeof(word), file) ) {
        char word2[Max_Letters];
        strcpy(word2, word);
        int index = tolower(word[0]) - 'a';
        insertmot(&lists[index] , word);
        insert_ed(List_ed, word2);
        insert_ing(List_ing, word2);
    }
    count_ed(List_ed);
    count_ing(List_ing);
    fclose(file);
}

void print_Num_Lists(){

    printf("\n\n");
    printf("                                                                       Statistics                                   \n");
    printf("                                                         ----------------------------------------          \n\n");
    printf("\t\t\t\t\t-----------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t|                        ---------------------------                         |\n");
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number Of Words is: %d                                                 |\n",countWords(lists));
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Anagrams is: %d                                      |\n", Lists_Anag);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Words That Are Lexically Close is: %d                |\n", Lists_OneDiff);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Words Fromed By Other Words (Preff_Suff) is: %d      |\n", Lists_PreffSuff);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Words That End With 'ing' is: %d                     |\n", Lists_ing);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Words That Are in The Past Participle is: %d         |\n", Lists_ed);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t| The Number of Lists of Words Formed By Adding One Letter At a Time is: %d   |\n", Lists_ajout_graduel);
    printf("\t\t\t\t\t|                                                                            |\n");
    printf("\t\t\t\t\t-----------------------------------------------------------------------------\n\n\n\n\n\n");

}

int main() {

    Maximize();
    Barrechargement();
    welcome();
    Welcome2();
    Chargement();
    printf("\n");
    int retour;
    pastP* List_ed = NULL;
    presentC* List_ing = NULL;
    main_anag* List_OneDiff = NULL;
    main_anag* List_Anagrams = NULL;
    main_anag* List_PreffSuff = NULL;
    main_anag* List_ajout_graduel = NULL;
    Read_File(lists, &List_ed, &List_ing);
    int choix;
    int insert;

    while (1) {

    Menu:
        system("cls");
        printf("\n");
        printf("                                                                         MENU                                   \n");
        printf("                                                       ----------------------------------------          \n\n");
        printf("\t\t\t\t\t**********************************************************************\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*                 ---------------------------                        *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   01. Display All The Words With Their Characteristic              *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   02. Fill & Display The Words Formed From Other Words By Adding   *\n");
        printf("\t\t\t\t\t*      a Prefix Letter Subsequence, in Suffix or in The Middle       *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   03. Display The Words in The Past Participle With 'ed'           *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   04. Display The Words in The 'ing' Form                          *\n", 130, 130);
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   05. Fill & Display The Anagrams                                  *\n", 130, 130);
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   06. Fill & Display The Closest Words Lexically                   *\n");
        printf("\t\t\t\t\t*     (One Letter Difference)                                        *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   07. Fill & Display The Words Formed By Gradually Adding One      *\n");
        printf("\t\t\t\t\t*       Letter At a Time                                             *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   08. Insert/Delete a Word                                         *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*   09. Display The Number Of Words & Lists Created                  *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t*               Any Other Key To Quit The Program                    *\n");
        printf("\t\t\t\t\t*                                                                    *\n");
        printf("\t\t\t\t\t**********************************************************************\n\n");
        Textecolor(5);

        printf("                                                 Enter your choice :\n");
        gotoxy(71, 34);
        printf(" _____ ");
        gotoxy(71, 35);
        printf("|     |");
        gotoxy(71, 36);
        printf("|_____|\n");
        gotoxy(74, 35);
        choix = getch() - '0'; // convert ASCII digit to integer value
        printf("%d", choix); // display user input
        Sleep(170);
        system("cls");
        Chargement();
        switch (choix) {
            case 1:
                print_words(lists);
                gotoxy(59, 36);
                printf("Press any key to return to the menu");
                gotoxy(59, 38);
                printf("Press 'ESCAPE' To Exit The Program");
                retour = getch();
                switch (retour)
                {
                    case ESC:
                        goto exit;
                        break;
                    default:
                        goto Menu;
                    }
                break;
            case 2:
                Textecolor(1);
                Lists_PreffSuff = 0;
                printf("                              The Words Formed From Other Words By Adding a Prefix Letter Subsequence, in Suffix or in The Middle Are: \n");
                Fill_pref_suff(lists, &List_PreffSuff);
                print_ListAnagram(List_PreffSuff);
                free_list_anag(List_PreffSuff);
                List_PreffSuff = NULL;
                goto press;
                break;
            case 3:
                Textecolor(4);
                print_list_ed(List_ed);
                free_list_ed(List_ed);
                goto press;
                break;
            case 4:
                Textecolor(4);
                print_list_ing(List_ing);
                free_list_ing(List_ing);
                goto press;
                break;
            case 5:
                Textecolor(8);
                Lists_Anag = 0;
                printf("                                                                     The Anagrams Are: \n");
                Fill_Anagrams(lists, &List_Anagrams);
                print_ListAnagram(List_Anagrams);
                free_list_anag(List_Anagrams);
                List_Anagrams = NULL;
                // gotoxy(59, 36);
                goto press;
                break;
            case 6:
                Textecolor(12);
                Lists_OneDiff = 0;
                printf("                                                The Closest Words Lexically(One Letter Difference) Are: \n") ;
                Fill_one_diff(lists, &List_OneDiff);
                print_ListAnagram(List_OneDiff);
                free_list_anag(List_OneDiff);
                List_OneDiff = NULL;
                goto press;

            case 7:
                Textecolor(1);
                Lists_ajout_graduel = 0;
                printf("                                      The Words Formed By Gradually Adding One Letter At a Time Are: \n");
                Fill_ajout_graduel(lists, &List_ajout_graduel);
                print_ListAnagram(List_ajout_graduel);
                free_list_anag(List_ajout_graduel);
                List_ajout_graduel = NULL;
                goto press;
                break;

            case 8:
                printf("\n");
                printf("\t\t\t\t\t\t                           MENU                                   \n");
                printf("\t\t\t\t\t\t                    -----------------------          \n\n");
                printf("\t\t\t\t\t\t\t\t*****************************\n");
                printf("\t\t\t\t\t\t\t\t*                           *\n");
                printf("\t\t\t\t\t\t\t\t*  ---------------------    *\n");
                printf("\t\t\t\t\t\t\t\t*                           *\n");
                printf("\t\t\t\t\t\t\t\t*   01. Insert a Word       *\n");
                printf("\t\t\t\t\t\t\t\t*                           *\n");
                printf("\t\t\t\t\t\t\t\t*   02. Delete a Word       *\n");
                printf("\t\t\t\t\t\t\t\t*                           *\n");
                printf("\t\t\t\t\t\t\t\t*****************************\n\n\n");
                printf("\t                                             Enter your choice :\n");
                gotoxy(75, 14);
                printf(" _____ ");
                gotoxy(75, 15);
                printf("|     |");
                gotoxy(75, 16);
                printf("|_____|\n");
                gotoxy(78, 15);
                scanf("%d",&insert);
                system("cls");
                switch (insert)
                {
                case 1:
                    insert_word(lists, &List_ing, &List_ed);
                    break;
                case 2:
                    delete_mot(lists);
                    break;
                }
                goto press;
                break;
            case 9:
                Textecolor(3);
                print_Num_Lists();
                goto press;
            default:
                free_table(lists);
                GoodBye();
                exit(1);
                break;
        }
    }
    press:
            gotoxy(59, 36);
            printf("Press any key to return to the menu");
            gotoxy(59, 38);
            printf("Press 'ESCAPE' To Exit The Program");
            retour = getch();
            switch (retour)
            {
                case ESC:
                    goto exit;
                    break;
                default:
                    goto Menu;
            }
    exit:
            free_table(lists);
            GoodBye();
            exit(1);
    return 0;
}
