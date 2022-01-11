#!/bin/bash
#!/bin/sh

function pm #This allows me to make it work through terminal, after doing source pm.sh
		#shell automatically take the arguement values in $1 and $2
{
	if [ -z "$2" ]; then
		echo "invalid, no second arguement" #regulates it to make sure the user puts a value in for the second arguement
	else
	
		if [ "$1" = "create_project" ]; then
			temp=temp.txt
	    		echo "$2" > "$temp"	#takes the second argument and puts it in to temp.txt for use in C
			gcc /home/pat/cw2/create_project.c -o create_project	#compiles the C code
			./create_project	#runs the C code
			cd "$2"	
			touch forgit.txt ;
			git add -A >/dev/null;			#the allows to fully make the master directory to allow the branches
			git commit -m "for git" >/dev/null;
			rm forgit.txt >/dev/null; 
			cd ..
			rm create_project	#removes C code to decrease clutter
						
		elif [ "$1" = "add_feature" ]; then
			copy="no"
			temp=temp.txt
	    		echo "$2" > "$temp"	#takes the second argument and puts it in to temp.txt for use in C
			gcc /home/pat/cw2/add_feature.c -o add_feature
			FILE=Makefile     
			if [ ! -f $FILE ]; then
				cp  /home/pat/cw2/Makefile .	#if the folder doesn't have Makefile in it to use, then it gets copied in
				copy="yes"
			fi
			./add_feature
			rm add_feature
			if [ "$copy" = "yes" ]; then		#removes makefile to reduce clutter
				rm Makefile
			fi

		elif [ "$1" = "add_tag" ]; then
			if ! grep -q -w "$2-" "/home/pat/cw2/tags"; then		#this stops there from being the same tag twice
				temp=temp.txt
				echo "$2" > "$temp"
				gcc /home/pat/cw2/add_tag.c -o add_tag	#runs the add_tag.c file
				./add_tag
				rm temp.txt	#removes more clutter
				rm add_tag
			else
				echo "This tag already exists"
			fi
						
		elif [ "$1" = "find_tag" ]; then
			temp="$2-"
			line=$(awk -v x="$temp" '$0~x {print NR}' tags)			#checks which line the tag is on, then checks that location on the taglocs, to see where it is and doesn't look like much cos the work i did in add_tag.c allows me to have less code over here
			loc= echo $(sed "${line}q;d" tagsloc) | sed -r 's/^.{12}//'
			

		elif [ "$1" = "output_svg" ]; then
			if [ -d "$2" ]; then
				echo $a;
				cd $2		#i found it easier just to go in to the directory where the project is
				gcc /home/pat/cw2/output_svg.c -o output_svg
				./output_svg
				grep -v "bin" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt
				grep -v "doc" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt		#these delete all the files that shouldnt be shown on the svg file
				grep -v "src" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt
				grep -v "test" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt
				grep -v "lib" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt
				grep -v "config" DrawWBS.txt > temp.txt; mv temp.txt DrawWBS.txt
				export line substitute
				line=2
				substitute="* $2"
				sed -i "${line}s/.*/$substitute/"  DrawWBS.txt
				java -jar /home/pat/cw2/plantuml.jar -tsvg DrawWBS.txt		#creates the svg from the .txt
				rm output_svg
				rm DrawWBS.txt
				cd ..

			fi
				
				
		else
			echo "invalid"	
		fi
			
#		elif [ "$1" = "move_by_tag" ]; then
#			if [ -z "$3" ]; then				#didnt manage to get this working, but it would have swapped the folders around, then swap their places on the tagsloc file
#				echo "invalid, no third arguement"
#			elif [ "$2" = "$3" ]; then
#				echo "invalid, both values the same"
#
#			else
#				echo "move by tag"
#				temp="$2-"
#				temp2="$3-"
#				
#				line=$(awk -v x="$temp" '$0~x {print NR}' tags)
#				echo "$line"
#				loc= echo $(sed "${line}q;d" tagsloc)
#				echo "$loc"
#				mkdir /home/pat/cw2/temp
#				cp -r "$loc" /home/pat/cw2/temp
#				rm -r "$loc"
#				line2=$(awk -v x="$temp2" '$0~x {print NR}' tags)
#				echo "$line2"
#				loc2= echo $(sed "${line2}q;d" tagsloc)
#				echo "$loc2"
#				cp -r "$loc2" "$loc"
#				rm -r "$loc2"
#				cp -r /home/pat/cw2/temp "$loc2"
#				rm -r /home/pat/cw2/temp
#				local TMPFILE=tmp.$$
#    				mv $loc $TMPFILE && mv $loc2 $loc && mv $TMPFILE $loc2 				
#				awk -v var="$line" -v var1="$line2" 'NR==var {
#  					s=$0
#  					for(i=var+1;i<var1;i++){
#    						getline;s=$0"\n"s
#  					}
#  					getline;print;print s
#  					next
#					}1' /home/pat/cw2/tagsloc			
#			fi

	
	
fi
}
echo "If you haven't done so already, please type source pm.sh"


