# filesystem-search

## idea
An programm out of two parts:
1. A background app that watches over a specific folders, files or filesystem and indexes it and provides and easy way for other apps to search in the index.
2. A cli app that can be used to: manage the background app, search the index, and show search results.

### Background app

#### watching over file changes
Code that inputs a folder path and a sincewhentolook DateTime, then looks at every last modified date of each file in the folder. It will retunr a list of all files that have a modified datetime after the inputed dateTime. After that it will start to look for any modification (inotifywait on linux) and will index that too and update the last modified sincewhentolook.

The speed of how the first part can be done can be very diffrent depenidng on read speed of the filesystem:

- SSD: 500 000 (files) * 0.1ms(on slower systems, it took 0.021695 in a vm) = 50ms(10ms with my speed). This should be way more than enough for the initial file test, even maybe maken the proposed inotifywait unneccesary.

- HDD: 500 000 (files) * 10ms(can be faster, but i cant test) = 83 minutes or less. here this approach would not be a good idea. but because i dont have a hdd system  i will not focus on hdds.

#### indexing and storing the index

#### providing access to other apps
