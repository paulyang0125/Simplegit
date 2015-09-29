#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "simplegit.h"
#include "util.h"

/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function description.
 * - Only edit this file (simplegit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size> (incl.
 *     NULL character) from file <filename> and store it into <str>. Note that <str>
 *     needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the homework spec.
 */

/* simplegit init
 *
 * - Create .simplegit directory
 * - Create empty .simplegit/.index file
 * - Create .simplegit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */
 

int simplegit_init(void) {
  fs_mkdir(".simplegit");

  FILE* findex = fopen(".simplegit/.index", "w");
  fclose(findex);

  FILE* fbranches = fopen(".simplegit/.branches", "w");
  fprintf(fbranches, "%s\n", "master");
  fclose(fbranches);
   
  write_string_to_file(".simplegit/.prev", "0000000000000000000000000000000000000000");
  write_string_to_file(".simplegit/.current_branch", "master");

  return 0;
}



/* simplegit add <filename>
 * 
 * - Append filename to list in .simplegit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int simplegit_add(const char* filename) {
  FILE* findex = fopen(".simplegit/.index", "r");
  FILE *fnewindex = fopen(".simplegit/.newindex", "w");

  char line[FILENAME_SIZE];
  
  
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);
      fclose(fnewindex);
      fs_rm(".simplegit/.newindex");
      return 3;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fprintf(fnewindex, "%s\n", filename);
  fclose(findex);
  fclose(fnewindex);

  fs_mv(".simplegit/.newindex", ".simplegit/.index");

  return 0;
}

/* simplegit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 * The status command in simplegit should read the file .simplegit/.index and print a line for each tracked file. The * exact format is described below. Unlike git status, simplegit status should not print anything about untracked 
 * files.
 
 
 output:
 
 $ simplegit status
Tracked files:

  <file1>
  [...]
  <fileN>

<N> files total
 
 
 */

int simplegit_status() {
  /* COMPLETE THE REST */
  
  //1. read the file .simplegit/.index
  
  FILE* findex = fopen(".simplegit/.index", "r");
  char line[FILENAME_SIZE];
  //char line[50];
  fprintf(stdout, "Tracked files:\n");
  fprintf(stdout, "\n");
  

  int numberOfLine; 
  numberOfLine = 0;
  
  //2. print a line for each tracked file
  while(fgets(line, sizeof(line),findex) != NULL)
	{
		// now we process the line
		strtok(line, "\n");
		fprintf(stdout, "  %s\n", line);
		numberOfLine++;
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "%d files total\n", numberOfLine);
  
  
  fclose(findex);

  return 0;
}

/* simplegit rm <filename>
 * 
 * See "Step 2" in the homework 1 spec.
 *
 */
 
 /*
 OUTPUT:
 $ simplegit rm FILE_THAT_IS_NOT_TRACKED.txt
ERROR: File <filename> not tracked

 */
 

int simplegit_rm(const char* filename) {
  
  /* COMPLETE THE REST */
  FILE *findex = fopen(".simplegit/.index", "r");
  FILE *fnewindex = fopen(".simplegit/.newindex", "w");
  
  char line[FILENAME_SIZE];
  
  int fileExistedFlag; 
  fileExistedFlag = 1; 
  
  //2. check line by line for each tracked file 
  while(fgets(line, sizeof(line),findex)){
	  strtok(line, "\n");	  
	  
	//3, write the line into .newindex when the file name is not the same as the checked line 
	  
  	if(strcmp(line, filename) != 0 ){  
  		fprintf(fnewindex, "%s\n", line);
  	}else{		  
  	  fileExistedFlag = 2;
  		  
  	}
	  
  }
	  
	  if (fileExistedFlag == 2){
		  fclose(findex);
      fclose(fnewindex);
		  fs_mv(".simplegit/.newindex", ".simplegit/.index");
		  return 0;
		  
	  }else{	  
		  fclose(findex);
      fclose(fnewindex);
		  fprintf(stderr, "ERROR: File %s not tracked\n", filename);
		  return 1;
		  		  
	  }
  fclose(fnewindex);
	fclose(findex);
  return 0;
}




/* simplegit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */
 
/*$ simplegit commit -m "G-O- -B-E-A-R-S-!"
ERROR: Message must contain "GO BEARS!"
 */
 
 

const char* go_bears = "GO BEARS!";

int is_commit_msg_ok(const char* msg) {
  /* COMPLETE THE REST */
  
  int indexOfmsg, indexOfgo_bear;
	indexOfgo_bear = 0;
  for (indexOfmsg = 0; msg[indexOfmsg] != '\0'; indexOfmsg++){
	  if (msg[indexOfmsg] == go_bears[indexOfgo_bear]){
		  
		indexOfgo_bear = indexOfgo_bear + 1;
	  }
	  else{
		  
		  indexOfgo_bear = 0;
		  
	  }
	  
	  if (indexOfgo_bear == strlen(go_bears)){		  
		  return 2;
		  
	  }
  }
  return 0;
}







void next_commit_id_part1(char* commit_id) {
  /* COMPLETE THE REST */
  int checker = 1;
  int i = 0;

  while (i < (COMMIT_ID_BYTES - COMMIT_ID_BRANCH_BYTES)) {
    switch(commit_id[i]) {
      case '0':
        commit_id[i] = '6';
        break;
      case '6':
        commit_id[i] = '1';
        checker = 0;
        break;
      case '1':
        commit_id[i] = 'c';
        checker = 0;
        break;
      case 'c':
        commit_id[i] = '6';
        break;
    }
    if (!checker) {
      break;
    } else {
      i += 1;
    }
  }
}




int simplegit_commit(const char* msg) {

  char current_branch[BRANCHNAME_SIZE];
  read_string_from_file(".simplegit/.current_branch", current_branch, BRANCHNAME_SIZE);

  if (!strlen(current_branch)) {
    fprintf(stderr, "ERROR: Need to be on HEAD of a branch to commit\n");
    return 1;
  }

 //First, check whether the commit string contains "GO BEARS!". If not, display an error message.
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", go_bears);
    return 1;
  }


  
  //Read the ID of the previous last commit from .simplegit/.prev
  char commitId[COMMIT_ID_SIZE];
  read_string_from_file(".simplegit/.prev", commitId, COMMIT_ID_SIZE);
  
  //Generate the next ID (newid) in such a way that:
  //default id:0000000000000000000000000000000000000000
  
  next_commit_id(commitId);

  /* COMPLETE THE REST */
  
  //1. create CommitFolder
  
  int offset = 10;
  char newCommitFolderPath[COMMIT_ID_SIZE + offset];
  sprintf(newCommitFolderPath, "%s%s", ".simplegit/", commitId); 
  fs_mkdir(newCommitFolderPath);

  //2. copy .simplegit/.index, .simplegit/.prev 
  char newIndexPath[COMMIT_ID_SIZE + offset * 2];
  sprintf(newIndexPath, "%s%s", newCommitFolderPath, "/.index");
  fs_cp(".simplegit/.index", newIndexPath);

  char newPrevPath[COMMIT_ID_SIZE + offset * 2];
  sprintf(newPrevPath, "%s%s", newCommitFolderPath, "/.prev");
  fs_cp(".simplegit/.prev", newPrevPath);

  //3.copy all tracked files into the directory

  char trackedFilePath[FILENAME_SIZE];
  FILE* indexFile = fopen(".simplegit/.index", "r");
	  
	while (fgets(trackedFilePath, sizeof(trackedFilePath), indexFile)) {
      strtok(trackedFilePath, "\n");
      char trackFileFolder[COMMIT_ID_SIZE + offset *3];
      sprintf(trackFileFolder, "%s/%s", newCommitFolderPath, trackedFilePath);
      fs_cp(trackedFilePath, trackFileFolder);
    }
	fclose(indexFile);
	
  //4.copy msg into "commitId"/msg and .prev
	
	char msgFilePath[COMMIT_ID_SIZE + offset *3];
    sprintf(msgFilePath, "%s/%s", newCommitFolderPath, ".msg");
    write_string_to_file(msgFilePath, msg);
    write_string_to_file(".simplegit/.prev", commitId);

 
  return 0;
}


/* simplegit log
 *
 * See "Step 4" in the homework 1 spec.
 * 
 */

int simplegit_log(int limit) {
  /* COMPLETE THE REST */


  //get the most recent id 
  int offset = 10;
  char commitId[COMMIT_ID_SIZE];
  char msgfolderpath[COMMIT_ID_SIZE + offset * 2];
  char msg[MSG_SIZE];
  char PrevPath[COMMIT_ID_SIZE + offset * 2];
  read_string_from_file(".simplegit/.prev", commitId, COMMIT_ID_SIZE);
  if (commitId[0] == '0') {
    fprintf(stderr, "ERROR: There are no commits!\n");
    return 1;
  }

  while (limit && (commitId[0] != '0')) {
    fprintf(stdout, "\n");
    fprintf(stdout, "commit %s\n", commitId);
    sprintf(msgfolderpath, ".simplegit/%s/.msg", commitId);
    read_string_from_file(msgfolderpath, msg, MSG_SIZE);
    fprintf(stdout, "    %s\n", msg);
    sprintf(PrevPath, ".simplegit/%s/.prev", commitId);
    read_string_from_file(PrevPath, commitId, COMMIT_ID_SIZE);
    limit -= 1;
  }
  fprintf(stdout, "\n");
  return 0;
}


const char* digits = "61c";

void next_commit_id(char* commit_id) {
  char current_branch[BRANCHNAME_SIZE];
  read_string_from_file(".simplegit/.current_branch", current_branch, BRANCHNAME_SIZE);

  // The first COMMIT_ID_BRANCH_BYTES=10 characters of the commit ID will
  // be used to encode the current branch number. This is necessary to avoid
  // duplicate IDs in different branches, as they can have the same pre-
  // decessor (so next_commit_id has to depend on something else).
  int n = get_branch_number(current_branch);
  for (int i = 0; i < COMMIT_ID_BRANCH_BYTES; i++) {
    commit_id[i] = digits[n%3];
    n /= 3;
  }

  // Use next_commit_id to fill in the rest of the commit ID.
  next_commit_id_part1(commit_id + COMMIT_ID_BRANCH_BYTES);
}


// This helper function returns the branch number for a specific branch, or
// returns -1 if the branch does not exist.
int get_branch_number(const char* branch_name) {
  FILE* fbranches = fopen(".simplegit/.branches", "r");

  int branch_index = -1;
  int counter = 0;
  char line[FILENAME_SIZE];
  while(fgets(line, sizeof(line), fbranches)) {
    strtok(line, "\n");
    if (strcmp(line, branch_name) == 0) {
      branch_index = counter;
    }
    counter++;
  }

  fclose(fbranches);

  return branch_index;
}

/* simplegit branch
 *
 * See "Step 5" in the homework 1 spec.
 *
 */

int simplegit_branch() {
  /* COMPLETE THE REST */

  FILE* fbranches = fopen(".simplegit/.branches", "r");
  char line[BRANCHNAME_SIZE];
  char current_branch[BRANCHNAME_SIZE];
  read_string_from_file(".simplegit/.current_branch", current_branch, BRANCHNAME_SIZE);

  while (fgets(line, sizeof(line), fbranches) != NULL) {
    strtok(line, "\n");
    if (strcmp(line, current_branch) == 0) {
      fprintf(stdout, "* %s\n", line);
    } else {
      fprintf(stdout, "  %s\n", line);

    }
  }
  fclose(fbranches);
  return 0;
}



/* simplegit checkout
 *
 * See "Step 6" in the homework 1 spec.
 *
 */

int checkout_commit(const char* commit_id) {
  /* COMPLETE THE REST */
  if (strcmp(commit_id, "0000000000000000000000000000000000000000") == 0) {
    write_string_to_file(".simplegit/.index", "");
  } else {
    FILE* findex = fopen(".simplegit/.index", "r");
    char line[BRANCHNAME_SIZE];
    while(fgets(line, sizeof(line), findex)) {
      strtok(line, "\n");
      fs_rm(line);
    }
    fclose(findex);
    char IndexPath[COMMIT_ID_SIZE + 20];
    sprintf(IndexPath, ".simplegit/%s/.index", commit_id);
    FILE* files = fopen(IndexPath, "r");
    char newline[BRANCHNAME_SIZE];
    while(fgets(newline, sizeof(newline), files)) {
      strtok(newline, "\n");
      char dest[COMMIT_ID_SIZE + BRANCHNAME_SIZE + 20];
      sprintf(dest, ".simplegit/%s/%s", commit_id, newline);
      fs_cp(dest, newline);
    }
    fclose(files);
    fs_cp(IndexPath, ".simplegit/.index");
    
  }
  write_string_to_file(".simplegit/.prev", commit_id);
  return 0;
}

int is_it_a_commit_id(const char* commit_id) {
  /* COMPLETE THE REST */
  int i = 0;
  while (commit_id[i] != '\0') {
    if ((commit_id[i] != '6') && (commit_id[i] != '1') && (commit_id[i] != 'c')) {
      return 0;
    }

    i += 1;
  }
  if (i == 40) {
    return 1;
  }
  return 0;
}

int simplegit_checkout(const char* arg, int new_branch) {
  // Get the current branch
  char current_branch[BRANCHNAME_SIZE];
  read_string_from_file(".simplegit/.current_branch", current_branch, BRANCHNAME_SIZE);

  // If not detached, update the current branch by storing the current HEAD into that branch's file...
  // Even if we cancel later, this is still ok.
  if (strlen(current_branch)) {
    char current_branch_file[BRANCHNAME_SIZE+50];
    sprintf(current_branch_file, ".simplegit/.branch_%s", current_branch);
    fs_cp(".simplegit/.prev", current_branch_file);
  }

  // Check whether the argument is a commit ID. If yes, we just stay in detached mode
  // without actually having to change into any other branch.
  if (is_it_a_commit_id(arg)) {
    char commit_dir[FILENAME_SIZE] = ".simplegit/";
    strcat(commit_dir, arg);
    if (!fs_check_dir_exists(commit_dir)) {
      fprintf(stderr, "ERROR: Commit %s does not exist\n", arg);
      return 1;
    }

    // Set the current branch to none (i.e., detached).
    write_string_to_file(".simplegit/.current_branch", "");

    return checkout_commit(arg);
  }

  // Just a better name, since we now know the argument is a branch name.
  const char* branch_name = arg;

  // Read branches file (giving us the HEAD commit id for that branch).
  int branch_exists = (get_branch_number(branch_name) >= 0);

  // Check for errors.
  if (branch_exists && new_branch) {
    fprintf(stderr, "ERROR: A branch named %s already exists\n", branch_name);
    return 1;
  } else if (!branch_exists && !new_branch) {
    fprintf(stderr, "ERROR: No branch %s exists\n", branch_name);
    return 1;
  }

  // File for the branch we are changing into.
  char branch_file[FILENAME_SIZE] = ".simplegit/.branch_"; 
  strcat(branch_file, branch_name);

  // Update the branch file if new branch is created (now it can't go wrong anymore)
  if (new_branch) {
    FILE* fbranches = fopen(".simplegit/.branches", "a");
    fprintf(fbranches, "%s\n", branch_name);
    fclose(fbranches);
    fs_cp(".simplegit/.prev", branch_file); 
  }

  write_string_to_file(".simplegit/.current_branch", branch_name);

  // Read the head commit ID of this branch.
  char branch_head_commit_id[COMMIT_ID_SIZE];
  read_string_from_file(branch_file, branch_head_commit_id, COMMIT_ID_SIZE);

  // Check out the actual commit.
  return checkout_commit(branch_head_commit_id);
}
