import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

import javax.swing.JFileChooser;

public class simpleVM {

public static void main(String[] args) throws IOException {
ArrayList<Integer> ref = new ArrayList<Integer>();//creating new HashSet
	int pgs=0;
	int frm=0;
	int pgReq=0;
	
try {   
	File inFile = new File("input.txt");
	Scanner sc = new Scanner(inFile);
	while (!sc.hasNextInt()) {
		sc.next(); // discard next token, which isn't a valid int
	}
	pgs = sc.nextInt(); // Pages
	frm = sc.nextInt(); // Frames
	pgReq = sc.nextInt(); // Page requests
//	System.out.printf("PAGES: %d,\t", pgs);
//	System.out.printf("FRAMES: %d,\t", frm);
//	System.out.printf("REQUESTS: %d\n", pgReq);
   
   while(sc.hasNext()) {
    String frame = sc.next();
    int frms = Integer.parseInt(frame);
    ref.add(frms);// add the integers to HashSet.
   }//end of while
  
   sc.close();//close the file
  
} catch (FileNotFoundException e) {
   System.err.println("FileNotFoundException: " + e.getMessage());
}

//display the size if it the set is not empty
if(!ref.isEmpty()){
   int size = ref.size();
//   System.out.println("The reference string lenght is: " + size);
}

//converting the arraylist to an array
   Integer frame[] = new Integer[ref.size()];
   frame = ref.toArray(frame);
   System.out.printf("\nPage Replacement Policies:\n");
   System.out.printf("\n1 :    FIFO\n2 :    LRU\n\n");
   System.out.printf("\nEnter a number between 1 and 2 to choose a page replacement policy: ");

   Scanner sc = new Scanner(System.in);
   while (!sc.hasNextInt()) {
   sc.next(); // discard next token, which isn't a valid int
   }
   int ch = sc.nextInt();

switch(ch){
   case 1: FIFO(frame,pgs,frm,pgReq);
   break;
   case 2: LRU(frame,ref.size());
   break;
   default: System.out.printf("\nInvalid entry, terminating now.\n");   
}
  
}
/**Simulates LRU page replacement for given reference string
* @throws IOException **/
public static void LRU(Integer[] page, int n) throws IOException {
int []frame = new int[10];
int []used = new int[10];
int index = 0;
int i,j,k,temp;
int flag=0,pf=0;
BufferedWriter wr = new BufferedWriter(new FileWriter("file.txt"));
PrintWriter out = new PrintWriter(wr);
System.out.printf("\tLRU Page Replacement");
System.out.printf("\nEnter number of Frames: ");
Scanner sc = new Scanner(System.in);
   while (!sc.hasNextInt()) {
   sc.next(); // discard next token, which isn't a valid int
   }
   int nf = sc.nextInt();
for(i=0;i<nf;i++)
   frame[i]= -1;

for(i=0;i<n;i++){
   flag=0;
   for(j=0;j<nf;j++){
    if(frame[j]==page[i]){//no fault
     System.out.printf("\n%d: ", page[i]);
     out.printf("\n%d: ", page[i]);
     flag=1;
     break;
    }
   }
   if(flag==0){//fault occurs
    for(j=0;j<nf;j++)
     used[j]=0;//all unused initially
    //moving through pages and searching recently used pages
    try{
     for(j = 0,temp= i-1;j < nf-1;j++,temp--){
      for(k = 0;k < nf;k++){
       if(frame[k]==page[temp])
        used[k]=1;
        //mark the recently used pages
      }
     }
    }
    catch(ArrayIndexOutOfBoundsException e){
    }
    for(j=0;j<nf;j++)
     if(used[j]==0)
      index=j;
    //replace the LRU page with new page
    frame[index]=page[i];
    System.out.printf("\n%d: ", page[i]);
    System.out.printf("--->F ");
    out.printf("\n%d: ", page[i]);
    out.printf("--->F ");
    pf++;//no of page faults
   }

   for(k= nf-1;k>=0;k--)
    if(frame[k] != -1){
     System.out.printf(" %d",frame[k]);//print frames
     out.printf(" %d",frame[k]);
    }
}

System.out.printf("\nNumber of page faults is: %d ",pf);
out.printf("\nNumber of page faults is: %d ",pf);
out.close();
wr.close();
}

/*///////////////////////////////////////////////////////////////////////
// FIFO page replacement policy simulation
//////////////////////////////////////////////////////////////////////*/
public static void FIFO(Integer[] pages, int pg, int frms, int rqsts) throws IOException {
int [] frame = new int[25];
int oldFrame=pages[0];
int i,k,avail,count=0;
BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
PrintWriter out = new PrintWriter(wr);
System.out.printf("FIFO\n");
out.printf("FIFO\n");
int j=0;

for(i=0;i<frms;i++){
frame[i]= -1;
}
for(i=0;i<rqsts;i++){
avail=0;
for(k=0;k<frms;k++)
	if(frame[k]==pages[i]){
		System.out.printf("Page %d already loaded into Frame %d\n",pages[i],k);
		out.printf("Page %d already loaded into Frame %d\n",pages[i],k);
		avail=1;
	}
	if (avail==0){
		if(i==rqsts){count=0;}
		if(count==frms){
			//System.out.printf("Page %d unloaded from Frame %d, ",frame[k],j);
			System.out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
			//out.printf("Page %d unloaded from Frame %d, ",frame[k],j);
			out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
			oldFrame=pages[j];
			count--;
		}
		count++;
		frame[j]=pages[i];
		System.out.printf("Page %d loaded into Frame %d\n",pages[i],j);
		out.printf("Page %d loaded into Frame %d\n",pages[i],j);
		j=(j+1) % frms;
		
	}
	if(avail==1){
		//System.out.printf("Page %d unloaded from Frame %d, ",frame[k],j);
		//System.out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
		//out.printf("Page %d unloaded from Frame %d, ",frame[k],j);
		//out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
	}
}
out.close();
wr.close();
}
}