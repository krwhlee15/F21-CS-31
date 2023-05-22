#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

bool decrypt(const char ciphertext[], const char crib[]);
void runtest(const char ciphertext[], const char crib[]);

int main()
{
    cout.setf(ios::boolalpha);

    runtest("Hirdd ?2 ejsy zu drvtry od.\nO'z fodvtrry.\n", "my!23?;secret");
    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");
    runtest("Rswjo qgx Tmeuo sgjsy jds vqgf vo jds vqzf xbby.\n"
			"Udbyjo iqcju cg wybgj cg jds esjqiqo zqy\n"
			"Xbg'j rsj jds jsrrsy jycn jds ucrsgj qrqyt.\n"
			"ZU 31 cu zdqrrsgecge!", "silent alarm");
    runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "   hush???hUSh---    --- until NovemBER !! ");
    runtest("F gspt fe! zyxZYXzyx--Abca abCa    bdefg## $$dsptrqtj6437 wvuWVUwvu\n\n8 9\n", "hush hush until november");

	return 0;
}

bool decrypt(const char ciphertext[], const char crib[]) {
   
   //Max Char : 71 * 91
	const int MAXCHAR = 6461;
	const int MAXSTR = 90;

    if (strlen(crib) > MAXSTR)
	{
        return false;
    }
    
    char user_crib[MAXSTR];
    
	strncpy(user_crib, crib, sizeof(user_crib));

	for (int i = 0; user_crib[i] != '\0'; i++)
	{
		user_crib[i] = tolower(user_crib[i]);
	}

    char text[MAXCHAR];
   
   //reset the array and copy
	memset(text, 0, sizeof(text));
	strncpy(text, ciphertext, sizeof(text));

	for (int i = 0; text[i] != '\0'; i++)
	{
		text[i] = tolower(text[i]);
	}

	int firstAlpha = 0;

    //make a array of crib without special characters
	char crib_clean[MAXSTR];
    int crib_clean_index = 0;
    for (int i = 0; i < MAXSTR; i++)
	{
        crib_clean[i] = '\0'; 
    }

	for (int i = 0; user_crib[i] != '\0'; i++)
	{
		if (isalpha(user_crib[i]))
		{
			firstAlpha = i;
			break;
		}
	}
    for (int i = firstAlpha; user_crib[i] != '\0'; i++)
	{
        if (isalpha(user_crib[i]))
		{
            crib_clean[crib_clean_index] = user_crib[i];
            crib_clean_index++;
        }
		else if (crib_clean_index > 0 && crib_clean[crib_clean_index-1] == ' ')
		{
            ;
        }
		else
		{
            crib_clean[crib_clean_index] = ' ';
            crib_clean_index++;
        }
    }
	
	//erase extra spaces at the end of the array
	for (int i = 0; crib_clean[i] != '\0'; i++)
	{
		if(crib_clean[i] == ' ')
		{
			for(int j = 1; 1; j++)
			{
				if(isalpha(crib_clean[i+j]))
				{
					break;
				}
				else if (crib_clean[i+j] == '\0')
				{
					for(int k = 0; k < j; k++)
					{
						crib_clean[i+k] = '\0';
					}
					break;
				}
			}
		}
	}
   
	char text_clean[MAXCHAR];
	int text_clean_index = 0;
	for (int i = 0; i < MAXCHAR; i++)
	{
		text_clean[i] = '\0';
	}

	for (int i = 0; text[i] != '\0'; i++)
	{
		if (isalpha(text[i]))
		{
			firstAlpha = i;
			break;
		}
	}

	for (int i = firstAlpha; text[i] != '\0'; i++)
	{
		if (isalpha(text[i]))
		{
			text_clean[text_clean_index] = text[i];
			text_clean_index++;
		}
		else if (text_clean_index > 0 && text_clean[text_clean_index-1] == ' ')
		{
			;
		}
		else
		{
			text_clean[text_clean_index] = ' ';
			text_clean_index++;
		}
	}

	//erase extra spaces at the end of the array
	for (int i = 0; text_clean[i] != '\0'; i++)
	{
		if(text_clean[i] == ' ')
		{
			for(int j = 1; 1; j++)
			{
				if(isalpha(text_clean[i+j]))
				{
					break;
				}
				else if (text_clean[i+j] == '\0')
				{
					for(int k = 0; k < j; k++)
					{
						text_clean[i+k] = '\0';
					}
					break;
				}
			}
		}
	}

	//separate into words
    const int MAXROW = 71;
    const int MAXCOL = 91;
    char separate[MAXROW][MAXCOL];
    for (int i = 0; i < MAXROW; i++)
	{
        for (int j = 0; j < MAXCOL; j++)
		{
            separate[i][j] = '\0';
        }
    }

    int word_n = 0;
    int char_n = 0;
    
	for (int index = 0; text_clean[index] != '\0'; index++)
	{
        if (text_clean[index] == ' ')
		{
            word_n++;
            char_n = 0;
        }
		else
		{
            separate[word_n][char_n] = text_clean[index];
            char_n++;
        }
    }
    
	//separate into words
    char crib_separate[MAXROW][MAXCOL];
    for (int i = 0; i < MAXROW; i++)
	{
        for (int j = 0; j < MAXCOL; j++)
		{
            crib_separate[i][j] = '\0';
        }
    }

    int crib_word_n = 0;
    int crib_char_n = 0;
    
	for (int index = 0; crib_clean[index] != '\0'; index++)
	{
        if (crib_clean[index] == ' ')
		{
            crib_word_n++;
            crib_char_n = 0;
        }
		else
		{
            crib_separate[crib_word_n][crib_char_n] = crib_clean[index];
            crib_char_n++;
        }
    }
    
    //compare length of the words with crib
	int match_word[MAXSTR];
    int match_word_index = 0;
    for (int i = 0; i < MAXSTR; i++)
	{
        match_word[i] = '\0';
    }

    for (int i = 0; i <= word_n; i++)
	{
        if (strlen(separate[i]) == strlen(crib_separate[0]))
		{
            for (int j = 1; j <= crib_word_n; j++)
			{
                if (strlen(separate[i+j]) != strlen(crib_separate[j]))
				{
                    break;
                }
				else if (j == crib_word_n)
				{
                    match_word[match_word_index] = i;
                    match_word_index++;
                }
            }
        }
    }
    
	//make a key
    char key[MAXCHAR/2][2];
    for (int i = 0; i < match_word_index; i++)
	{ 
        int key_index = 0;
        for (int j = 0; j <= crib_word_n; j++)
		{
            for (int k = 0; k < strlen(crib_separate[j]); k++)
			{ 
                key[key_index][0] = separate[(match_word[i]+j)][k];
                key[key_index][1] = crib_separate[j][k];
                key_index++;
            }
        }
		
		//check if the key is valid
        int text_match = 0;
        int crib_match = 0;
        for (int j = 0; j < key_index; j++)
		{ 
            for (int k = 0; k < key_index; k++)
			{
                if (key[j][0] == key[k][0])
				{
                    text_match++;
                    if (key[j][1] != key[k][1])
					{
                        goto checkMatch;
                    }
                    crib_match++;
                }
            }
        }
		
        if (crib_match == text_match)
		{
            for (int j = 0; j < MAXCHAR; j++)
			{
                for (int k = 0; k < key_index; k++)
				{
                    if (key[k][0] == text[j])
					{
                        text[j] = toupper(key[k][1]);
                    }
                }
            }

            for (int j = 0; text[j] != '\0'; j++) {
                cout << text[j];
            }
            
            return true;
        }
        checkMatch: ;
    }

    return false; 
}

void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}


