//Stuti Rana
//85039361


#include "hw1.h"


struct Stats {
	unsigned num_char;
	unsigned num_lines;
	unsigned num_words;
	unsigned longest_line;
};


// You may define any helper functions you want. Place them in helpers.c/.h
bool is_valid(char* modif){
	if (strcmp(modif,"-U")==0){
		return true;
	}else if(strcmp(modif,"-L")==0){
		return true;
	}else if(strcmp(modif,"-T")==0){
		return true;
	}else if(strcmp(modif,"-t")==0){
		return true;
	}else if(strcmp(modif,"-R")==0){
		return true;
	}else if(strcmp(modif,"-W")==0){
		return true;
	}else{
		return false;
	}
}

bool is_findingword(char* modif){
	if (strcmp(modif,"-U")==0){
		return false;
	}else if(strcmp(modif,"-L")==0){
		return false;
	}else if(strcmp(modif,"-T")==0){
		return false;
	}else if(strcmp(modif,"-t")==0){
		return false;
	}else if(strcmp(modif,"-R")==0){
		return false;
	}else if(strcmp(modif,"-W")==0){
		return true;
	}else{
		return false;
	}
}

void print_err(){
	fprintf(stderr,"ERROR! Usage: ./formattxt -L | -U | -T | -t | -R SYMBOLS [-W WORD]\n\n");
	return;
}

void write_to_STDERR(struct Stats e){
	fprintf(stderr,"%d\n%d\n%d\n%d\n",e.num_char,e.num_lines,e.num_words,e.longest_line);
	return;
}

int read_stats(char* modif, char* modif2 ,char * word){

	//read from input line by line
	char * line =NULL;
	size_t len =0;
	ssize_t char_num;


	unsigned total_char=0;
	unsigned line_num = 0;
	unsigned num_words = 0;
	int longest = 0;
	int uq_word =0;
	//get line also reads the number of characte read inludeing the delimiter character but no including the terminating null byte
	char_num = getline(&line,&len,stdin);
	
	// if it is an empyt file AND
	//if the first modification isn't valid 
	
	if (char_num==-1 || is_valid(modif)==false){
		print_err();
		struct Stats everything = {total_char,line_num,num_words,longest};
   		return 1;
   	}
   	// if the first or second modification is W 
   	// and there is no word
   	
	while(char_num>-1){
		
		
		

		

   		if (line[char_num-1]==10){
   			
   			if ((char_num-1) > longest){
        		longest = char_num-1;
        	}
   		}else{
   			if (char_num > longest){
        		longest = char_num;
        	}
   		}
       	total_char +=char_num;
        
		
		num_words+=count_words(line);
		int size = strlen(line);
		
		if(line[size-1] == '\n'){
        	line_num++;
        }
        if(is_findingword(modif2)&&strcmp(modif,"-R")!=0){
			uq_word+=call_modification(modif2, line,word);
		}

		uq_word+=call_modification(modif, line,word);
		if (strcmp(modif,"-t")!=0 && strcmp(modif,"-R")!=0){
   			printf("%s", line);
   		}

        char_num = getline(&line,&len,stdin);        
	}
	
	if (longest ==0){
		print_err();
		struct Stats everything = {total_char,line_num,num_words,longest};
   		return 1;
	}
	struct Stats everything = {total_char,line_num,num_words,longest};
		
   	if(line){
   		free(line);
   	}
   	write_to_STDERR(everything);
   	
   	if(strcmp(modif,"-W")==0|| strcmp(modif2,"-W")==0){
   		fprintf(stderr, "%d\n", uq_word);
   	}
   	
	return 0;
   	
}

int count_words(char * line){
	int num_words = 0;
	//count the number of words in current line
	int at_word = 0; // at space
	int i = 0;
	while(line[i]!='\0'){
			if (at_word==0){//the previous thing was a space
				if (isspace(line[i])==0){//we are now at a char
					num_words++;
					at_word=1;// we are now in a word
				}
			}
			else if (at_word==1){//we are in a word
				if (isspace(line[i])){//we hit a space
					at_word=0;//we are now in a space
				}
			}
			i++;
		}
	return num_words;
}

void upper(char* cap){
	int i = 0;
		while(cap[i]!='\0'){
			if (isalpha(cap[i]) && islower(cap[i])){
				cap[i]-=32;
			}
			i++;
		}
}
void lower(char* cap){
	int i = 0;
		while(cap[i]!='\0'){
			if (isalpha(cap[i]) && isupper(cap[i])){
				cap[i]+=32;
			}
			i++;
		}
}
void title(char* cap){
	//count the number of words in current line
		int at_word = 0; // at space
		int i = 0;
		while(cap[i]!='\0'){
			
			if (at_word==0){//the previous thing was a space
				if (isspace(cap[i])==0 && isalpha(cap[i])){//we are now at a word
					at_word=1;
					if (isalpha(cap[i]) && islower(cap[i])){// if it is a lette and it is lower case
						cap[i]-=32;// capitalize
					}
				}
			}else if (at_word==1){//we are in a word
				if (isspace(cap[i])==0){//we are at a letter
					if (isalpha(cap[i]) && isupper(cap[i])){//id the letter is uppercase and a letter 
						cap[i]+=32;//lower case it
					}
				}else{//we hit a space
					at_word=0;
				}
			}
			i++;
		}
}
void print_to_term(char* line){
	int i = 0;
	char nl = '\n';
	int size = strlen(line);
	while(i<size){
		if (((i+1)%80)!=0&&line[i]!=10){
			printf("%c",line[i]);
		}
		else if(((i+1)%80)==0&&line[i]!=10){
			printf("%c",line[i]);
			printf("%c",nl);
		}
		i++;
	}
	
	if(((i-1)%80)!=0 && line[size-1]==10){
        printf("%c",nl);
    }
}
int find_words(char *line , char * word){
	
	int yes,count, i, j;
	int line_s, word_s;

	line_s = strlen(line);
	
	word_s = strlen(word);
	count =0;
	for(i =0; i <=line_s-word_s; i++){// we will go through one letter and look to see if it matches the entire word
		// so you want to subtract the length of the the word cuz when you get to the last one
		// you don't want to go over
		yes = 1; // default and if it passes through the loop it won't change
		for(j=0; j<word_s;j++){
			
			if(line[i+j]!= word[j]){// oh does the first letter match? go through no? break;
				yes = 0;
				break;
			}
		}
		if (yes==1){
			count++;
		}
	}
	return count;
}

void remove_char(char *line, char c){
	// hopefully this chages the actually line
	char * final =line;
	
	
	while(*line){// we want to go trhgouh the entire line for each character
		

		if(*line!= c){
			*final++ =*line++;
			
		}else{
			line++;
		}
	}
	*final = '\0';
}

void remv(char* line, char* word){
	// we go through the line and where we find the first character 
	// we will delete it in the character array
	// we will ten go to the next charcter and try to find it and delte it
	
	int j, word_s;
	
	word_s = strlen(word);
	for(j=0; j<word_s;j++){

		remove_char(line,word[j]);
		
	}
	printf("%s",line);
	return ;
}

int call_modification(char* modif, char* line, char * word){
	int count = 0;
	if (strcmp(modif,"-U")==0){
		upper(line);
	}else if(strcmp(modif,"-L")==0){
		lower(line);
	}else if(strcmp(modif,"-T")==0){
		title(line);
	}else if(strcmp(modif,"-t")==0){
		print_to_term(line);
	}else if(strcmp(modif,"-R")==0){
		remv(line,word);
	}else if(strcmp(modif,"-W")==0){
		count = find_words(line,word);
	}
	return count;
}

// Main program
int main(int argc, char *argv[]) {
	//I DONT KNOW IF THE SECOND IS ALWAYS THE INPUT FILE 
	//CHANGE THIS LATER IF NEEDED
	// a get request with 3rd param being stdin
	int s=1;
	char * word="NOT INT";
	char * modif2 = "NOT INT";
	if(argc == 2){
		if(is_findingword(argv[1])){
			print_err();
   			return 1;
		}else{
			s = read_stats(argv[1],modif2,word);
		}
	}else if(argc ==3){
		if (!is_findingword(argv[1]) &&strcmp(argv[1],"-R")!=0){//there are two arguements passed when its not a word
			print_err();
   			return 1;
		}else if(is_valid(argv[1])&&is_findingword(argv[2])){// there are two arguements and no word
			print_err();
   			return 1;
		}else{
			s = read_stats(argv[1],modif2,argv[2]);
		}
	}else if(argc ==4){
		if (is_valid(argv[1]) && !is_findingword(argv[2])){//there are two arguements passed when its not a word
			print_err();
   			return 1;
		}else{
			s = read_stats(argv[1],argv[2],argv[3]);
		}
	}
	// AM GETTING THE WRONG NUMBER OF WORDS WAT IS HAPPENING
	
	
    
    
    return s;
}
