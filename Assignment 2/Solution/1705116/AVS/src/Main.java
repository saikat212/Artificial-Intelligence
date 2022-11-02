import java.util.Scanner;
import java.io.*;
import  java.util.Random;


public class Main {
    public  static final int MAX_DEPTH=15;
    private static final int nBins=6;
    private static final int nStones=4;
    private static final int nMaxStages=150;
    private static final int NO_GAMES_PER_HEURISTIC=50;
    private static final int MAX_ORDER=1;
    private static double  win=0;
    private static double loss=0;
    private static int tie=0;
    private static  boolean isManual=true;
    private static  boolean isFinite=false;





    public static void main(String[] args) throws IOException{
        int h[]={0,0};
        int depth=MAX_DEPTH;
        int bins,stones;
        Scanner scanner=new Scanner(System.in);

        if(isManual)
        {
            System.out.println("Select a heuristic [0-6] for 0th player(Human-0)");
            h[0]=scanner.nextInt();
            System.out.println("Select a heuristic [0-6] for 1th player(Human-0)");
            h[1]=scanner.nextInt();

            System.out.println("Enter Depth to search: ");
            depth=scanner.nextInt();
            bins=nBins;
            stones=nStones;
            MancalaBoard.printBoardConfiguration();
            playLoop(selectStrategy(h[0]),selectStrategy(h[1]),depth,bins,stones);

        }
        else
        {
            for (int i=1;i<=6;i++)
            {

                for (int j=1;j<=6;j++)
                {
                    if(i!=j)
                    {
                        System.out.println("Heuristic Pair ("+i+" ===>> "+j+" ) \n");

                        h[0]=i;

                        h[1]=j;


                        depth=10;
                        bins=nBins;
                        stones=nStones;
                        //MancalaBoard.printBoardConfiguration();
                        for(int k=1;k<=100;k++)
                        {
                            playLoop1(selectStrategy(h[0]),selectStrategy(h[1]),depth,bins,stones);
                        }
                        System.out.println("Heuristic"+i+" Winned="+win+"(against Heuristic"+j+")");
                        System.out.println("Heuristic"+i+" lost="+loss+"( against Heuristic"+j+" )");
                        double ratio=0;
                        try {
                            ratio=(win/loss)*100;
                        }catch (ArithmeticException e)
                        {

                            isFinite=true;
                        }
                        if(isFinite)
                        {
                            System.out.println("Win-Loss Ratio : 100/0");
                            isFinite=false;
                        }
                        else
                        {
                            System.out.println("Win-Loss Ratio of Heuristic"+i+"="+ratio+"%");
                        }

                        win=0;
                        loss=0;
                        tie=0;
                    }

                }
            }

        }


    }

    public static void playLoop(MancalaHeuristic s0,MancalaHeuristic s1,int MAX_DEPTH,int bins,int stones) {

         play(bins,stones,s0,s1,MAX_DEPTH);
    }

    public static void playLoop1(MancalaHeuristic s0,MancalaHeuristic s1,int MAX_DEPTH,int bins,int stones) {

        play1(bins,stones,s0,s1,MAX_DEPTH);
    }

    private static MancalaHeuristic selectStrategy(int n) {return MancalaHeuristic.intToStrategy(n);}


    private static void play(int bins,int stones,MancalaHeuristic s0,MancalaHeuristic s1,int MAX_DEPTH) {
        MancalaBoard board=new MancalaBoard(bins,stones,s0,s1,MAX_DEPTH);

        System.out.println(board);
        int round=0;
        while (!board.isGameOver() && round <nMaxStages) {
            System.out.println("-----------"+round+"-----------");
            int currentPlayer=board.currentPlayer();
            System.out.println("Player "+currentPlayer+"\'s move.");
            int bin=board.move();
            if(bin<=0) break;
            //System.out.println("Player "+currentPlayer+" selects "+board.stonesMoved()+" stones from bin "+bin);
            System.out.println(board);
            System.out.println("\n\n\n--------------------------------\n\n\n");
            round++;
        }
        System.out.println("Final board configuration: \n");
       System.out.println(board);
        if(board.getBin(0,0)==board.getBin(1,0)) {
             System.out.println("Match Tie !!!");


        }else if(board.getBin(0,0)>board.getBin(1,0)){
             System.out.println("Player0 wins !!!");


        }else
        {
            System.out.println("Player1 wins !!!");

        }
    }


    private static void play1(int bins,int stones,MancalaHeuristic s0,MancalaHeuristic s1,int MAX_DEPTH) {
        MancalaBoard board=new MancalaBoard(bins,stones,s0,s1,MAX_DEPTH);

        int round=0;
        while (!board.isGameOver() && round <nMaxStages) {
            //System.out.println("-----------"+round+"-----------");
            int currentPlayer=board.currentPlayer();
            //System.out.println("Player "+currentPlayer+"\'s move.");
            int bin=board.move();
            if(bin<=0) break;
            //System.out.println("Player "+currentPlayer+" selects "+board.stonesMoved()+" stones from bin "+bin);
            //System.out.println(board);
            //System.out.println("\n\n\n--------------------------------\n\n\n");
            round++;
        }
        //System.out.println("Final board configuration: \n");
        // System.out.println(board);
        if(board.getBin(0,0)==board.getBin(1,0)) {
            //System.out.println("Match Tie !!!");
            tie++;

        }else if(board.getBin(0,0)>board.getBin(1,0)){
            //System.out.println("Player0 wins !!!");
            win++;

        }else
        {
            //System.out.println("Player1 wins !!!");
            loss++;
        }
    }
}
