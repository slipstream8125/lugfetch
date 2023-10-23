/*
 * This needs lot of clean up
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#define COLOR_LINE 5
#define COLOR_TEXT 7
#define COLOR_TITLE 4
#define COLOR_ASCII 3
using namespace std;

string left_info[][2] = {
	{ "OS",		"Arch Linux" },
	{ "HOST",	"Swift SFX14-41G" },
	{ "KRNL",	"   6.5.7" },
	{ "CPU",	"Ryzen 5 5600X" },
	{ "GPU 0",	"NVIDIA RTX 3050" },
	{ "GPU 1",	"AMD Radeon Vega 7" },
	{ "RAM",	"5888MiB / 15341MiB" }
};

string right_info[][2] = {
	{ "WM",		"bspwm " },
	{ "TERM",	"Alacritty" },
	{ "FONT",	"Iosevka " },
	{ "THM",	"Gruvbox" },
	{ "SHL",	"oh-my-zsh" },
	{ "PKGS",	"859 (pacman)" },
	{ "UPT",	"1d 13h 57m" }
};

string colors[] = {
	"\x1B[30m",
	"\x1B[31m",
	"\x1B[32m",
	"\x1B[33m",
	"\x1B[34m",
	"\x1B[35m",
	"\x1B[36m",
	"\x1B[37m",
	"\033[0m" // Reset color character
};

// Outputs text with the escape color code prefixed
string color(string text, int n) {
	return colors[n] + text;
}

// ASCII characters for the boxes
string chars[] = {
	color("─", COLOR_LINE),
	color("╭", COLOR_LINE),
	color("╮", COLOR_LINE),
	color("╰", COLOR_LINE),
	color("╯", COLOR_LINE),
	color("", COLOR_LINE),
	color("", COLOR_LINE),
	color("│", COLOR_LINE),
};

// The ASCII art is manually padded with spaces to the right
string ascii = R""""(              &BGBB#&   #B#&                    
               &#GPGGB#  BGG#                   
                  #GGGGB#BGGG#                  
                   #GGGGGGGGGG&                 
                    &BGGGGGGGGGGBBB###BB&       
                      BGPPGG5J7!!7Y5PPPY7YB&    
                     #G?~557^:....:^^~?PP5GG&   
                   &B5!:^!^::......~?JYBBBGGG#  
                  #G5~:::::......:5&@@@@@@@&##& 
                 BGP!:::::......!B              
                #GG?:::::.....:J&               
               &GGP~::::.....!G                 
               BGG5^::::...~5                   
              #GGG5^:::...!#                    
             #GGGGP~:::...P                     
         &&#BGGGGGG7:::..^#                     
     &&#BGY?!~~!7J5J:::..~&                     
   &######BGPPP555PPJ^::.!&                     
                     #5!::~JG&                  
                       &GJ7JY55#                
                            &&                  
)"""";

// Creates a box with title and text. Padding adds extra space to the given side.
string createBox(string title, string text, string titleSide = "left", int padding = 10, string paddingSide = "left") {
	string s="";
	
	int horizontal_width = size(text) + 4;

	string top_line = "";
	for (int i = 0; i < horizontal_width - 7 - size(title); i++) {
		top_line += chars[0];
	}
	// string top_line(horizontal_width - 7 - size(title), chars[0]);

	string bottom_line = "";
	for (int i = 0; i < horizontal_width - 2; i++) {
		bottom_line += chars[0];
	}

	if (paddingSide == "left") {
		s += string(padding - horizontal_width, ' ');
		if (titleSide == "right") s += chars[1] + top_line + chars[5] + " " + color(title, COLOR_TITLE) + " " + chars[6] + chars[0] + chars[2] + "\n";
		else s += chars[1] + chars[0] + chars[5] + " " + title + " " + chars[6] + top_line + chars[2] + "\n";

		s += string(padding - horizontal_width, ' ');
		s += chars[7] + " " + color(text, COLOR_TEXT) + " " + chars[7] + "\n";
		s += string(padding - horizontal_width, ' ');
		s += chars[3] + bottom_line + chars[4] + "\n";
	} else {
		if (titleSide == "right") s += chars[1] + top_line + chars[5] + " " + color(title, COLOR_TITLE) + " " + chars[6] + chars[0] + chars[2];
		else s += chars[1] + chars[0] + chars[5] + " " + color(title, COLOR_TITLE) + " " + chars[6] + top_line + chars[2];
		s += string(padding - horizontal_width, ' ') + "\n";

		s += chars[7] + " " + color(text, COLOR_TEXT) + " " + chars[7];
		s += string(padding - horizontal_width, ' ') + "\n";
		s += chars[3] + bottom_line + chars[4];
		s += string(padding - horizontal_width, ' ') + "\n";
	}

	return s;
}

// Generate the boxes from info after calculating the required padding
string generateLeftBoxes() {
	string s = "";

	// Get longest line length for padding
	int maxWidth = 0;
	for (int i = 0; i < size(left_info); i++) {
		if (maxWidth < size(left_info[i][1])) {
			maxWidth = size(left_info[i][1]);
		}
	}

	// Create a padded box for every item in the info array
	for (int i = 0; i < size(left_info); i++) {
		s += createBox(left_info[i][0], left_info[i][1], "right", maxWidth + 4, "left");
	}

	return s;
}

// Generate the boxes from info after calculating the required padding
string generateRightBoxes() {
	string s = "";

	// Get longest line length for padding
	int maxWidth = 0;
	for (int i = 0; i < size(right_info); i++) {
			// cout << max < size(info[i][1]) << endl;
		if (maxWidth < size(right_info[i][1])) {
			maxWidth = size(right_info[i][1]);
		}
	}

	// Create a padded box for every item in the info array
	for (int i = 0; i < size(right_info); i++) {
		s += createBox(right_info[i][0], right_info[i][1], "left", maxWidth + 4, "right");
	}

	return s;
}

// Absolutely gigachad operator overloading that prints multiline strings horizontally next to each other
// Thanks to lastchance on https://cplusplus.com/forum/beginner/257126/
string operator *( const string a, const string b )
{
   const string SPACE = "  ";
   stringstream ssa( a ), ssb( b );
   string result, parta, partb;
   while( getline( ssa, parta ) && getline( ssb, partb ) ) result += parta + SPACE + partb + '\n';
   return result;
}

int main() {

	// Color the ASCII art
	istringstream f(ascii);
	string line;    
	string colored_ascii = "";
	while (getline(f, line)) {
		colored_ascii += color(line, COLOR_ASCII) + "\n";
	}

	cout << endl;
	cout << generateLeftBoxes() * colored_ascii * generateRightBoxes();
	cout << endl;
}
