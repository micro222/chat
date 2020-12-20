#include "template_functions.h"

void search_file(void)
{
    /*
    search file for matching template
     read line, if EOL return fail
     remove comments
     extract template
     split template
     check template for match
    extract info
     extract function_name
     extract arg1
     extract arg2
     change arguments if they are integers
    return success
    call function
    */
#define MAX 150
    int n;
    int numberofwords;
    FILE *templates;
    char output[80];
    int status;
    char* file_status;
    int result;

// open file
    templates = fopen("templates2.txt","r");
    if(templates == NULL)
    {
        sprintf(output, "fopen failed while trying to open templates2.txt\n");
        puts(output);
    }

// search line by line
    while(1)
    {
        // read a line
        file_status = fgets(template_line, 100, templates);
//printf("TLine:%s\n",template_line);////////////////////////////
        if (file_status==0){printf("\nEOF"); return;}
        remove_comments();
        result = extract_template();
 //       printf("el:%d\n", result);
        if (result == 0) continue; // next line
 //       printf("tf46:%s\n", template1); //ok

        split_template();


        match = compare_template();  // fail
 //       printf("tf49\n");////////////////////////////
        if(match == 1)printf("\nMATCH\n  ");

        if(match == 1) break;
    } // get another template if there's no match
//printf("483\n");////////////////////////////
    fclose(templates);

    printf("TW:");
    for(n=1; n<=numberoftemplatewords; n++) printf("%s ", template_words[n]);
    extract_function_name();               printf(" func: %s ", function_name);
    extract_arg1();                        printf(" arg1: %s ", arg1);
    extract_arg2();                        printf(" arg2: %s ", arg2);

 result = atoi(arg1);
 if(result > 0){strcpy(arg1, user_words[result]); }
 printf(" arg1b: %s ", arg1);

 result = atoi(arg2);
 if(result > 0){strcpy(arg2, user_words[result]); }
 printf(" arg2b: %s \n", arg2);

 return;

}
////////////////////////////////

int extract_template(void)
{
    int letter_position;
    line_position =0;

    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)

    {
        // End of template_line?

        if(template_line[line_position]==0 )
        {
            template1[letter_position] = 0;
         //   printf("null:%s\n", template1);
            return 0;
        }
        if(line_position >=  0x10|| line_position >= 0x13)
        {
            template1[letter_position] = 0;
            printf("crlf:%s\n", template1);
            return 0;
        }
        //end of word?
        if(template_line[line_position] == ',')
        {
            template1[letter_position] = 0;  // terminate the word
            line_position++;
             //printf("105:%s\n", template1);////////////////////////////
            return letter_position;
        }
        template1[letter_position] = template_line[line_position];
        line_position++;
    //    printf("110:%s\n", template1);
    }
    return 0;
}

void split_template()
{

    int letter_position = 0;
    int word_position = 1;

    for(line_position = 0; line_position < sizeof(template1); line_position++)
    {

        if(template1[line_position]==0)
        {
            template_words[word_position][letter_position] = 0;
            numberoftemplatewords = word_position ;
/*
            printf("t1%s\n", template_words[1]);
printf("t2%s\n", template_words[2]);
printf("t3%s\n", template_words[3]);
 printf("u1:%s\n", user_words[1]);//
 printf("u2:%s\n", user_words[2]);//
 printf("u3:%s\n", user_words[3]);//

*/

            return;
        }

        if(template1[line_position] == ' ')
        {
            template_words[word_position][letter_position] = 0;  // terminate the word
            word_position++;
            letter_position = 0;
            continue;
        }
        template_words[word_position][letter_position] = template1[line_position];
        letter_position++;
    }
}

int compare_template()
{
    int n;
    //match = 1; // match
  // printf("num %d\n", numberoftemplatewords);////////////////////////////
    for(n=0; n<numberoftemplatewords; n++)
    {

 //printf("tem%s\n", template_words[n]);
 //printf("user:%s\n", user_words[n]);////////////////////////////
 //printf("483\n");////////////////////////////
        if(strcmp(user_words[n], template_words[n] ) == 0 ||
                (strcmp(template_words[n], "*") == 0))        {
        }
        else return 0;
    }
    return 1;
}


void remove_comments(void)
{
//        status = 1;
    int n;

    for(n=0; n< MAX; n++)
    {
        if(template_line[n] == '/')
        {
            template_line[n] = 0;    // terminate the string
            return;
        }
        else if(template_line[n] == 0)
        {
            //              status = 0;
            return;
        }
    }

}


void extract_function_name(void){

    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the comma
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++){
        //end of function name?
        if(template_line[line_position] == ','){
            function_name[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        function_name[letter_position] = template_line[line_position];
        line_position++;
    }
}


void extract_arg1(void){
    int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the space
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of arg1?
        if(template_line[line_position] == ',')
        {
            arg1[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        arg1[letter_position] = template_line[line_position];
        line_position++;
    }
}


void extract_arg2(void){
   int letter_position;

    if(template_line[line_position] == ',' ) line_position++; // skip over the space
    if(template_line[line_position] == ' ' ) line_position++; // skip over the space
    for(letter_position = 0; letter_position < MAX_LETTERS; letter_position++)
    {
        //end of arg2?
        if(template_line[line_position] == ' '  )
        {
            arg2[letter_position] = 0;  // terminate the word
            line_position++; // skip over the comma
            return;
        }
        arg2[letter_position] = template_line[line_position];
        line_position++;
    }
}

int str_to_int(char* s){
  if (s[0] < '0' || s[0] > '9') return 0;
  return s[0] - '0';
}

/////////////////////////////////
