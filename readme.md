# filesystem-search

## idea
An programm out of two parts:
1. A background app that watches over a specific folders, files or filesystem and indexes it and provides and easy way for other apps to search in the index.
2. A cli app that can be used to: manage the background app, search the index, and show search results.

### Background app

The app will be a standart c++ app. when installing the background app e.g as a deb, it will run a post install script to create a systemctl service and automaticlly enable it. by default it will not scan as the app will look for a config file which doesnt exist yet and will then just turn off again.

#### watching over file changes
Code that inputs a folder path and a sincewhentolook DateTime, then looks at every last modified date of each file in the folder. It will retunr a list of all files that have a modified datetime after the inputed dateTime. After that it will start to look for any modification (inotifywait on linux) and will index that too and update the last modified sincewhentolook.

The speed of how the first part can be done can be very diffrent depenidng on read speed of the filesystem:

- SSD: 500 000 (files) * 0.1ms(on slower systems, it took 0.021695 in a vm) = 50s(10s with my speed). This should be way more than enough for the initial file test, even maybe maken the proposed inotifywait unneccesary.

- HDD: 500 000 (files) * 10ms(can be faster, but i cant test) = 83 minutes or less. here this approach would not be a good idea. but because i dont have a hdd system  i will not focus on hdds.

! This speed can be slower when reading mtime on thousends of files at the same time. It might be good to use async io or multithreading to decrease io wait times.

new files will be automaticly dedected as theri mtime is after last accessed.

deleted files will not be checked. whenever a search gets requested the programm will look if the files from the search results still exist, if not it will simply exclude it and (if possible) remove it from the index.

#### indexing and storing the index

each documents gets accessed, normalized:
- all to lowercase
- remove keywords as 'and, or, as'
- remove characters as '. , - _ ! ?' (only a-z, A-Z(will be lowercased), 0-9)
- stem the words.

for stopwords and stemming the words to work prooperly it needs to be dedcted which language the document is in, this can be added later when starting to support more languages.

For about 2 millions diffrent words it takes around 4s.

then it will add it to an inverted index with the documents path.

-> without optimization on storage a index with around 500000 files with average 200 words it could reach 1GB in index size.
#### providing access to other apps

#### storing other data
- config ~/.config/filesystem-search/config
- logs and erros /var/log/filesystem-search /log or /error


