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
			rqsts = sc.nextInt(); // page request
			
			while(sc.hasNext()){
				String frame = sc.next();
				frms = Integer.parseInt(frame);
				str.add(frms);
			}
			sc.close(); //close file
		}catch(FileNotFoundException e){
			System.err.println("FileNotFoundException: " + e.getMessage());
		}
		
		//check for stringlist, can't be empty
		if(!str.isEmpty()){
			size = str.size();
		}
		//convert the stringlist into an array
		Integer frame[] = new Integer[str.size()];
		frame = str.toArray(frame);
		System.out.printf("\nPage Replacement Policies:\n");
		System.out.printf("\n1 :    FIFO\n2 :    LRU\n\n");
		System.out.printf("\nEnter a number between 1 and 2 to choose a page replacement policy: ");
		Scanner sc = new Scanner(System.in);
		
		while (!sc.hasNextInt()) {
			System.out.printf("Invalid entry, try again:\n");
			sc.next(); // discard token, which is not valid a bit
		}
		sel = sc.nextInt();
		switch(sel){
		   case 1: FIFO(frame,pgs,frm,rqsts);
		   break;
		   //case 2: LRU(frame,pgs,frm,rqsts);
		   case 2: LRU(frame,frm, str.size());
		   break;
		   default: System.out.printf("\nInvalid entry, terminating program now.\n");   
		}
	}
	///// LRU PAGE REPLACEMENT POLICY SIMULATION //////
	public static void LRU(Integer[] page, int frm, int n) throws IOException {
		int []frame = new int[10];
		int []used = new int[10];
		int index = 0;
		int i,j,k,temp;
		int flag=0,pf=0;
		BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
		PrintWriter out = new PrintWriter(wr);
		System.out.printf("LRU");

		//int nf = frm;
		for(i=0;i<frm;i++)
		   frame[i]= -1;

		for(i=0;i<n;i++){
			flag=0;
			for(j=0;j<frm;j++){
				if(frame[j]==page[i]){//no fault
					System.out.printf("\n%d: ", page[i]);
					out.printf("\n%d: ", page[i]);
					flag=1;
					break;
				}
			}
			if(flag==0){//fault occurs
				for(j=0;j<frm;j++)
					used[j]=0;//all unused initially
				//moving through pages and searching recently used pages
				try{
					for(j = 0,temp= i-1;j < frm-1;j++,temp--){
						for(k = 0;k < frm;k++){
							if(frame[k]==page[temp])
								used[k]=1;
								//mark the recently used pages
						}
					}
				}catch(ArrayIndexOutOfBoundsException e){
				}
				for(j=0;j<frm;j++)
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

			for(k= frm-1;k>=0;k--)
				if(frame[k] != -1){
					System.out.printf(" %d",frame[k]);//print frames
					out.printf(" %d",frame[k]);
				}
		}
		out.close();
		wr.close();
	} // END OF LRU
	///// FIFO page replacement policy simulation //////
	public static void FIFO(Integer[] pages, int pg, int frms, int rqsts) throws IOException {
	int i,k,loaded,cnt=0, j=0;
	int [] frame = new int[25];
	int oldFrame=pages[0];
	BufferedWriter wr = new BufferedWriter(new FileWriter("output.txt"));
	PrintWriter outfile = new PrintWriter(wr);

	System.out.printf("FIFO\n");
	outfile.printf("FIFO\n");

	for(i=0;i<frms;i++){ // Initialize frames to -1
		frame[i]= -1;
	}
	for(i=0;i<rqsts;i++){
	loaded=0;
	for(k=0;k<frms;k++)
		if(frame[k]==pages[i]){
			loaded=1;
		}
		if (loaded==0){
			if(i==rqsts){cnt=0;}
			if(cnt==frms){
				System.out.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
				outfile.printf("Page %d unloaded from Frame %d, ",oldFrame,j);
				oldFrame=frame[(j+1)%frms];
				cnt--;
			}
			cnt++;
			frame[j]=pages[i];
			System.out.printf("Page %d loaded into Frame %d\n",pages[i],j);
			outfile.printf("Page %d loaded into Frame %d\n",pages[i],j);
			j=(j+1) % frms;
			
		}
		if(loaded==1){
			System.out.printf("Page %d already loaded into Frame %d\n",pages[i],k);
			outfile.printf("Page %d already loaded into Frame %d\n",pages[i],k);
		}
	}
	outfile.close();
	wr.close();
	} // END OF FIFO
}