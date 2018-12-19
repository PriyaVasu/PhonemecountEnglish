/************************************************************************************************
 *    			Phoneme Count in English language					*
 *												*
 *												*
 * 	Date of Written : 23.02.18			Final Modified Date :	28.02.18	*
 *												*
 *      Roll No : 17AT92P05				Mailid: priyagdarshi@yahoo.com		*
 * **********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char input1[20];	// Read Phoneme file
  char input2[20];	// Read lexword file
  char input3[20];	// Read lexpho file 
  char input4[20];	// Read Sentence file 	 	
  char output1[20];	// Output 
}FileDetails;
typedef struct {
  char pho[3];	// pho - phoneme.
  int np;	// np - number of phoneme occurence
}Phoneme;
typedef struct {
char lexword[40];	// lexicon word.
char lexpho[80];	// lexicon phoneme.
}Lexicon;
typedef struct {
  char Aword[40];
  char Mword[40];
  char Wordpho[80];
}WordinSentence;
typedef struct {
  char sentence[150];
  int nows;
  WordinSentence *WinSen;
}Sentences;

FileDetails ReadFileDetails(FileDetails fpd){
  // Function is to read the input and output file from offline.txt
  FILE *fp1 = fopen("Offline.txt","r");
  if(fp1 == NULL) {
    printf("\nOffline.txt doesn't exist\n");
    exit(1);
  } else {
    fscanf(fp1, "%s", fpd.input1);
    fscanf(fp1, "%s", fpd.input2);
    fscanf(fp1, "%s", fpd.input3);
    fscanf(fp1, "%s", fpd.input4);
    fscanf(fp1, "%s", fpd.output1);
  }
  fclose(fp1);
  return fpd;
}
FILE *FilePointerToRead(FILE *fp, char *fname){
  // To read the file pointer name  
  fp = fopen(fname,"r");
  if(fp == NULL){
    printf("\nError in %s file openeing\n", fname);
    exit(1);
  }
  return fp;
}
Phoneme *initializePhonemePtr(Phoneme *A, int nop) {
  int a, b;
  for(a = 0; a < nop; a++) {
    A[a].np = 0;		
  }
  return A;
}
Phoneme *CreatePhonemePtr(Phoneme *A, int nop) {
  A = (Phoneme*) malloc(nop * sizeof(Phoneme));
  if(A == NULL) {
    printf("\nError in memory allocation of bus pointer\n");
    exit(1); 
  }
  
  A = initializePhonemePtr(A, nop);
  
  return A;
}
Phoneme *ReadPhoneme(Phoneme *A, char *fname, int nop) {
  int i;
  FILE * fp2;
  fp2 = fopen(fname,"r");
  if(fp2 == NULL) {
    printf("\nFile %s doesn't exist", fname);
    exit(1);
  }
  for(i = 0; i < nop; i++) {
    fscanf(fp2, "%s", A[i].pho);
  }
  fclose(fp2);
return A;
}
void PrintPhoneme(Phoneme* A, int nop) {
  int i;
  printf("\n\t\tPhonenes are as follows\n\n");
  for(i = 0; i < nop; i++) {
    printf("%s\n", A[i].pho);
  } 
}
int ReadingNumberofLines(int nol, FILE* fp) {
  int count;
  char c;
  count = 0;

  for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
  nol = count;

  return nol;
}
Lexicon *initializeLexPtr(Lexicon *A, int n) {
  int i, j, k;
  for(i = 0; i < n; i++) {
    for(j = 0; j < 40; j++) 
      A[i].lexword[j] = 0; 
    for(k = 0; k < 80; k++) 
      A[i].lexpho[k] = 0; 
  }
  return A;
}
Lexicon *CreateLexPtr(Lexicon *A, int n) {

  A = (Lexicon*) malloc(n * sizeof(Lexicon));

  if(A == NULL) {
    printf("\nError in memory allocation of bus pointer\n");
    exit(1); 
  }

  A = initializeLexPtr(A, n);

  return A;
}
Lexicon *ReadLexiconWordFile(Lexicon *A, int n, char *fname) {
  int i;
  FILE * fp2;
  fp2 = fopen(fname,"r");
  if(fp2 == NULL) {
    printf("\nFile %s doesn't exist", fname);
    exit(1);
  }
  for(i = 0; i < n; i++) {
    fscanf(fp2, "%[^\n]%*c", A[i].lexword);
  }

  fclose(fp2);

  return A;
}
void PrintLexword(Lexicon* A, int n) {
  int i;
  printf("\n\t\tLexicon words are as follows\n\n");
  for(i = 0; i < n; i++) {
     printf("%s\n", A[i].lexword);
  } 
}
Lexicon *ReadLexiconPhoFile(Lexicon *A, int n, char *fname) {
  int i;
  FILE * fp2;
  fp2 = fopen(fname,"r");
  if(fp2 == NULL) {
    printf("\nFile %s doesn't exist", fname);
    exit(1);
  }
  for(i = 0; i < n; i++) {
    fscanf(fp2, "%[^\n]%*c", A[i].lexpho);
  }

  fclose(fp2);

  return A;
}
void PrintLexPho(Lexicon* A, int n) {
  int i;
  printf("\n\t\tLexicon Phonems are as follows\n\n");
  for(i = 0; i < n; i++) {
     printf("%s\n", A[i].lexpho);
  } 
}
Sentences *InitializeSentencesPtr(Sentences *A, int nos, int nows) {
  int i, j, k, l, m;
  
  for(i = 0; i < nos; i++) {
    A[i].nows = 0;
    for(j = 0; j < 150; j++) 
      A[i].sentence[j] = 0;
  }
  for(i = 0; i < nos; i++) {
    for(k = 0; k < nows; k++) {
      for(l = 0; l < 20; l++) {
	A[i].WinSen[k].Aword[l] = 0;
	A[i].WinSen[k].Mword[l] = 0;
      }
      for(m = 0; m < 20; m++) 
	A[i].WinSen[k].Wordpho[m] = 0;
    }
  }
  return A;
}
Sentences *CreateSentPtr(Sentences *A, int nos, int nows) {
  int i;
  A = (Sentences *)malloc(nos * sizeof(Sentences));
  if(A == NULL) {
    printf("\nError in memory allocation\n\n");
    exit(1);
  }
  
  for(i = 0; i < nos; i++) {
    A[i].WinSen = (WordinSentence *)malloc(nows * sizeof(WordinSentence));
    if(A[i].WinSen == NULL) {
      printf("\nError in memory allocation - internal loop\n\n");
      exit(1);
    }    
  }
  
  A = InitializeSentencesPtr(A, nos, nows);
  
  return A;
}
Sentences *ReadSentenceinput(Sentences *A, int nos, char *fname) {
  int i;
  FILE * fpa;
  fpa = fopen(fname,"r");
  if(fpa == NULL) {
    printf("\nFile %s doesn't exist", fname);
    exit(1);
  }
  for(i = 0; i < nos; i++) {
    fscanf(fpa, "%[^\n]%*c", A[i].sentence);
    // printf("%s\n", A[i].sentence);
  }
  
  fclose(fpa);
  return A;
}
void PrintSentences(Sentences *A, int nos){
  int i;
  printf("\nInput Sentences are as follows\n\n");
  for(i = 0; i < nos; i++) {
    printf("%s\n", A[i].sentence);
  }
}
Sentences *SentencetoWordSplit(Sentences *A, int ia) {
  char *ar, *f1;
  char *pch;
  int nows;
  
  nows = 0;
  
  ar = A[ia].sentence;
  // printf("%s\n", ar); // Testing purpose
  pch = strtok (ar," ,.-");
  
  while (pch != NULL) {
    f1 = pch;
    strcpy(A[ia].WinSen[nows].Aword, f1);
    strcpy(A[ia].WinSen[nows].Mword, f1);
    // printf ("%s\n",A[ia].WinSen[nows].Aword); // Use Mword or Aword to check
    nows = nows + 1;
    // A = ComparePhoneme(A, f1,nop);
    pch = strtok (NULL, " ,.-");
  }
  A[ia].nows = nows;
  // printf("\n%s", A[ia].sentence);
  return A;
}
Sentences *ConvertingLowerCasetoUpper(Sentences *A, int ia, int ib) {
  int i, j;
  char *fa;
  
  fa = A[ia].WinSen[ib].Aword;
  // printf("%s\n", fa);
  for(i = 0; i <= strlen(fa); i++) {
    if(fa[i]>=97 && fa[i]<=122) {
      fa[i]=fa[i]-32; }
  }
     
  return A;
}
void PrintLoweandUppWord(Sentences *A, int ia, int ib){
  printf("\%20s", A[ia].WinSen[ib].Mword);
  printf("%20s", A[ia].WinSen[ib].Aword);
}
FILE *FileWriting(FILE *fw, Sentences *A, int ia, int ib) {
  fprintf(fw,"%s\n",A[ia].WinSen[ib].Mword);
  return fw;
}
Sentences *CompareWithLexicon(Sentences *A, Lexicon *B, int ia , int ib, int nol, FILE *fw) {
  int i, cnt;
  
  cnt = 1;
  i = 0; 
  
  do {
    if( strcmp(A[ia].WinSen[ib].Aword,B[i].lexword) == 0) { // word present in lexicon
      strcpy(A[ia].WinSen[ib].Wordpho,B[i].lexpho);
      // printf("%s", A[ia].WinSen[ib].Wordpho);
      cnt = 0;
      if(cnt == 0) {
	break;
      }
    } else {
        cnt = 1; 
    }
    i = i + 1;
  } while(i < nol); 
  
  if( (cnt == 1) && (i == nol) )
     fw = FileWriting(fw, A, ia, ib);
  
  return A;
}
void PrintWinSenPhoneme(Sentences *A, int ia, int ib) {
  printf("\n%s", A[ia].WinSen[ib].Wordpho);
}
Phoneme *initializePhonemeCntPtr(Phoneme *A, int n) {
  int i;
  for(i = 0; i < n; i++)
    A[i].np = 0;
  return A;
}
Phoneme *ComparePhoneme(Phoneme *A, char *f1, int nop) {
  int i, index, count;
  
  // printf("\nReprint : %s\n", f1);
  index = 0; count = 0;
  for(i = 0; i < nop; i++) {
    if(strcmp(A[i].pho,f1) == 0) {
      index = i;
      count = count + 1;
      // printf("\n\t\tThird time : %s pho : %s\n", f1, A[i].pho);
    }
  }
  if(count != 0)
    A[index].np = A[index].np + count;
    
  return A;
}
Phoneme *ReadPhoneCount(Phoneme *A, Sentences *B, int ia, int ib, int nop) {
  char *ar, *f1;
  char *pch;
  
  ar = B[ia].WinSen[ib].Wordpho;
  // printf("\tFirst time %s\n", ar); // Testing purpose
  // printf ("Splitting string \"%s\" into tokens:\n",ar);
  pch = strtok (ar," ,.-");
  while (pch != NULL) {
    f1 = pch;
    // printf ("\nSecond time : %s\n",f1);
    A = ComparePhoneme(A, f1,nop);
    pch = strtok (NULL, " ,.-");
  }
  return A;
}
void PrintPhoneAndOccurence(Phoneme *A, int nop) {
  int i;
  printf("\n\t\tPhonenes are as follows\n\n");
  printf("**************************************\n");
  printf("Phoneme \t No of occurence\n**************************************\n");
  for(i = 0; i < nop; i++) {
    printf("  %s \t --> \t %d\n", A[i].pho, A[i].np);
  }
  printf("**************************************\n");
}
FILE *WritingPhoneEveryWord(FILE *fpo1, Phoneme *Phone, int nop, int aa) {
  int i;
  fprintf(fpo1,"\n");
  fprintf(fpo1,"%d,", aa+1);
  for(i = 0; i < nop; i++) {
    fprintf(fpo1,"%d,", Phone[i].np);
  }
  
  return fpo1;
}
FILE *FilePointerCreation(FILE* fpo2, char *fname) {
  fpo2 = fopen(fname,"w");
  if(fpo2 == NULL) {
    printf("\nError in creating %s", fname);
    exit(1);
  }
  
  return fpo2;
}
FILE *WritingInitallHeader(FILE *fpo1, Phoneme *Phone, int nop) {
  int i;
  fprintf(fpo1,"Words,Ph,on,em,e ,-->,\n");
  fprintf(fpo1,"Sent_No,");
  
  for(i = 0; i < nop; i++) {
    fprintf(fpo1,"%s,", Phone[i].pho);
  }
  
  return fpo1;
}


// *************************** Main Program *************************** //

int main(int argc, char* argv[]) {

  int nop, nos, nol, nows, i, j;	// nop - number of phoneme, nos - number of senetences, nol - number of lexicons 
  
  nop = 39; nows = 20; // number of words in each sentence maximum
  
  FileDetails fpd = ReadFileDetails(fpd);
  
  FILE *fp1 = FilePointerToRead(fp1,fpd.input1); // Reading first input file - phoneme.txt 

  Phoneme *Phone = CreatePhonemePtr(Phone, nop); // Creatin phoneme pointer

  Phone = ReadPhoneme(Phone, fpd.input1, nop); // Read Phoneme from file
  // PrintPhoneme(Phone, nop);
  
  FILE *fp2 = FilePointerToRead(fp2,fpd.input2); // Reading second input file - lexword.txt
  
  printf("\n\t\tWelcome to phoneme count program for english language\n\n\n\n");
  
  nol = 0; // initialization
  nol = ReadingNumberofLines(nol, fp2); 
  // printf("\nNumber of lines in %s is %d\n\n", fpd.input2, nol);
  
  Lexicon *Lex = CreateLexPtr(Lex, nol);
  fclose(fp2);

  Lex = ReadLexiconWordFile(Lex, nol, fpd.input2);
  // PrintLexword(Lex, nol);
  
  Lex = ReadLexiconPhoFile(Lex, nol, fpd.input3);
  // PrintLexPho(Lex, nol);
  
  FILE *fp4 = FilePointerToRead(fp4,fpd.input4); // Reading fourth input file sentence.txt
  
  nos = 0; // initialization
  nos = ReadingNumberofLines(nol, fp4); 
  // printf("\nNumber of lines in %s is %d\n\n", fpd.input4, nos);
  fclose(fp4); 
    
  Sentences *Sent = CreateSentPtr(Sent,nos, nows);
    
  Sent = ReadSentenceinput(Sent, nos, fpd.input4);
  // PrintSentences(Sent, nos);
  
  FILE *fw = fopen("Nonexist.txt", "a+"); // file to write worst case
  fprintf(fw,"\n ***** No lexicon exist for few word(s) in a sentences ***** \n"); 
  fprintf(fw, "------ For 0 Sentence ------\n");
  
  FILE *fpo1 = FilePointerCreation(fpo1, fpd.output1);
  
  fpo1 = WritingInitallHeader(fpo1, Phone, nop);
  
  for(i = 0; i < nos; i++) { // For every sentences 
    
    Sent = SentencetoWordSplit(Sent, i);
    
    Phone = initializePhonemeCntPtr(Phone, nop);
            
    for(j = 0; j < Sent[i].nows; j++) {
       Sent = ConvertingLowerCasetoUpper(Sent, i, j);
       // PrintLoweandUppWord(Sent, i, j); printf("\n");
       
       Sent = CompareWithLexicon(Sent, Lex, i , j, nol, fw);
       // PrintWinSenPhoneme(Sent, i, j); printf("\n");
       
       Phone = ReadPhoneCount(Phone, Sent, i, j, nop);
       // PrintPhoneAndOccurence(Phone, nop);
    }
    fpo1 = WritingPhoneEveryWord(fpo1, Phone, nop, i);
    
    fprintf(fw,"\n------ For %d Sentence ------\n", i+1);
  }
  printf("\n\nProgram Ends! Please check %s for output\n\n\n", fpd.output1);
  
  // Memory free
  fclose(fp1); free(Phone); free(Lex);
  for(i = 0; i < nos; i++)
    free(Sent[i].WinSen);
  free(Sent); fclose(fw); fclose(fpo1);
  
  return 0; 
}
