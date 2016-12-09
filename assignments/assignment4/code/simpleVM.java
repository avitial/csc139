/*
File: simpleVM.java
CSC139 
Fall 2016
Fourth Assignment
Avitia, Luis
Section # 01
OS: Linux
*/
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

public class simpleVM{
	public static void main(String[] args) throws IOException{
		int pgs=0;
		int frm=0;
		int rqsts=0;
		int sel=0;
		int frms, size;
		ArrayList<Integer> str = new ArrayList<Integer>();

		try{   
			File inFile = new File("input.txt");
			Scanner sc = new Scanner(inFile);			
			//check for valid bit (integer)
			while (!sc.hasNextInt()){
				sc.next(); // discard token, which isn't a valid int
			}
			pgs = sc.nextInt(); // pages
			frm = sc.nextInt(); // frames
			rqsts = sc.nextInt(); // page requests
			//get all the page requests
			while(sc.hasNext()){
				String frame = sc.next();
				frms = Integer.parseInt(frame);
				str.add(frms);
			}
			sc.close(); //close file
		}catch(FileNotFoundException e){
			System.err.println("FileNotFoundException: " + e.getMessage());
		}
		//check for stringlist, cannot be empty
		if(!str.isEmpty()){
			size = str.size();
		}
		//convert the stringlist into an array
		Integer frame[] = new Integer[str.size()];
		frame = str.toArray(frame);
		//request selection of a replacement policy
		System.out.printf("\nPage Replacement Policies:\n");
		System.out.printf("\n1 :    FIFO\n2 :    LRU\n\n");
		System.out.printf("\nEnter a number between 1 and 2 to choose a page replacement policy: ");
		Scanner sc = new Scanner(System.in);
		//check input is an integer
		while (!sc.hasNextInt()){
			System.out.printf("Invalid entry, try again:\n");
			sc.next(); // discard token, which is not valid a bit
		}
		sel = sc.nextInt();
		//make a decision based on user inpu
		switch(sel){
		   case 1: FIFO(frame,frm,rqsts);
		   break;
		   case 2: LRU(frame,frm, rqsts);
		   break;
		   default: System.out.printf("\nInvalid entry, terminating program now.\n");   
		}
	}
	///// LRU PAGE REPLACEMENT POLICY SIMULATION //////
	public static void LRU(Integer[] page, int frm, int rqsts) throws IOException{
		int []frame = new int[10];
		int []usedPgs = new int[10];
		int index=0;
		int currFrm=0;
		int i,j,k,m,tmp;
		int flag=0;
		int cnt=0;
		
		BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
		PrintWriter outfile = new PrintWriter(wr);
		System.out.printf("LRU\n");
		for(i=0;i<frm;i++)
		   frame[i]= -1;
		for(i=0;i<rqsts;i++){
			flag=0;
			for(j=0;j<frm;j++){
				if(frame[j]==page[i]){//page is currently loaded in frame
					System.out.printf("Page %d already in Frame %d\n",page[i],(j+1)%frm);
					outfile.printf("Page %d already in Frame %d\n",page[i],(j+1)%frm);					
					flag=1;
					break;
				}
			}
			if(flag==0){
				for(j=0;j<frm;j++)
					usedPgs[j]=0;//all frames unused initially
				try{//go through all pages and search for recently used pages
					for(j=0,tmp=i-1; j<frm-1; j++,tmp--){
						for(k=0; k<frm; k++){
							if(frame[k]==page[tmp])
								usedPgs[k]=1;//flag recently used pages
						}
					}
				}catch(ArrayIndexOutOfBoundsException e){
				}
				for(j=0,m=frm-1;j<frm;j++,m--)
					if(usedPgs[j]==0){
						index=j;
						currFrm=m;
					}
				//replace the LRU page with new page
				if(i==rqsts){cnt=0;}
				if(cnt==frm){
					System.out.printf("Page %d unloaded from Frame %d, ",frame[index],currFrm);
					outfile.printf("Page %d unloaded from Frame %d, ",frame[index],currFrm);
					cnt--;
				}
				frame[index]=page[i];
				cnt++;
				System.out.printf("Page %d loaded into Frame %d\n",frame[index],currFrm);
				outfile.printf("Page %d loaded into Frame %d\n",frame[index],currFrm);
			}
		}
		//close files
		outfile.close();
		wr.close();
	} // END OF LRU
	///// FIFO page replacement policy simulation //////
	public static void FIFO(Integer[] pages, int frms, int rqsts) throws IOException{
	int i,k,loaded,cnt=0, j=0;
	int [] frame = new int[25];
	int oldFrame=pages[0];

	BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
	PrintWriter outfile = new PrintWriter(wr);
	System.out.printf("FIFO\n");
	outfile.printf("FIFO\n");

	//initialize frames to -1
	for(i=0;i<frms;i++){
		frame[i]= -1;
	}
	for(i=0;i<rqsts;i++){
	loaded=0;
	for(k=0;k<frms;k++)
		if(frame[k]==pages[i]){
			loaded=1;
		}
		//start loading pages into frames
		if(loaded==0){
			//wait until all frames are used to start unloading
			if(cnt==frms){
				System.out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
				outfile.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
				oldFrame=frame[(j+1)%frms];
				cnt--;
			}
			frame[j]=pages[i];
			System.out.printf("Page %d loaded into Frame %d\n",pages[i],j);
			outfile.printf("Page %d loaded into Frame %d\n",pages[i],j);
			j=(j+1) % frms;
			cnt++;
		}
		//page is currently loaded in frame
		if(loaded==1){
			System.out.printf("Page %d already in Frame %d\n",pages[i],k);
			outfile.printf("Page %d already in Frame %d\n",pages[i],k);
		}
	}
	//close files
	outfile.close();
	wr.close();
	} // END OF FIFO
}