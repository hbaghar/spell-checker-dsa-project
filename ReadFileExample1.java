import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ReadFileExample1 {
    //LevenshteinDistance obj=new LevenshteinDistance();
    private static final String FILENAME = "H:\\Semester 2\\DSA\\work\\wordlist.txt";
    static String dict[];
    static long startTime;
    static long endTime;
    static long duration;
    public void binsearch(String s,int b,int e){

        int f=0;
        startTime=System.nanoTime();
        while(b<=e)
        {
        int m=(b+e)/2;
        if(dict[m].equalsIgnoreCase(s)){
            System.out.println("Found");
            f=1;
            break;
        }
        if(dict[m].compareTo(s)>0)
            e=m-1;
        else
            b=m+1;
        }
        
        //LevenshteinDistance obj=new LevenshteinDistance();
        //int w=obj.computeDistance(dict[(int)((b+e)/2)],s);
        
        if(f==0){
            for(int i=0;i<dict.length;i++){
                LevenshteinDistance obj=new LevenshteinDistance();
                int w=obj.computeDistance(dict[i],s);
                if(w<=1)
                    System.out.println(dict[i]);
            }
        }
        endTime=System.nanoTime();
        duration=(endTime-startTime);
    }
    public static void main(String[] args)throws IOException {

        BufferedReader br = null;
        FileReader fr = null;
        
        dict=new String[354936];

        try {

            fr = new FileReader(FILENAME);
            br = new BufferedReader(fr);

            String sCurrentLine;

            br = new BufferedReader(new FileReader(FILENAME));
            int i=0;

            while ((sCurrentLine = br.readLine()) != null) {
                dict[i++]=sCurrentLine;
            }

        } catch (IOException e) {

            e.printStackTrace();

        } finally {

            try {

                if (br != null)
                    br.close();

                if (fr != null)
                    fr.close();

            } catch (IOException ex) {

                ex.printStackTrace();

            }

        }
        
        int ch=1;
        Scanner sc=new Scanner(System.in);
        ReadFileExample1 obj=new ReadFileExample1();
        while(ch!=0){
            System.out.println("Enter the word to check");
            String z=sc.next();            
            obj.binsearch(z,0,354936);
            System.out.println("It takes "+duration+" nano seconds");
            System.out.println("Press 0 to exit 1 to conitnue");
            ch=sc.nextInt();
        }
    }
}
        


