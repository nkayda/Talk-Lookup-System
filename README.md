<h3>CS Talks Lookup System</h3>
<h4>Loading a .txt file | Terminal-based UI | Filtering Implementation</h4>
<p>
  Create a program that reads all the talk information from a file and provide an interface for the user to
query talk entries. Your program must support the following functionalities as options:
</p>
<ul>
  <li>
    Option 1: to load a talks file – ask the user to input the name of the file containing talk information
and load the entries from that file (report # of entries). Note that the file can be non-existent (if
so the program should print the error and keep running), but if it exists you can assume the format
inside that file is consistent (duration, talk title, overview, ---), with each line having at most 300
characters. It is possible for the user to load a different file by choosing this option again, which
will replace the previously loaded entries. You can assume the filename as at most 50 characters.
  </li>
  <li>
    Option 2: to list talks sorted by duration – list the talk entries from shortest to longest. If with the
same duration there are more than one talk entry, any order within that duration is acceptable.
  </li>
  <li>
    Option 3: to list talks sorted by title – list the talk entries sorted by title (as determined by strcmp).
If with the same title there are more than one talk entry, any order within that title is acceptable.
  </li>
  <li>
    Option 4: to lookup a talk – ask the user for a talk title for at most 50 characters (space included),
then report all entries containing the input as a substring. There can be more than one entry from
the file. The lookup is case-sensitive (i.e., “computer” and “Computer” are not the same).
  </li>
  <li>
    Option 5: to terminate the program – thank the user and end the program.
  </li>
  
</ul>
