import java.util.Scanner;

public class UserHeuristic extends MancalaHeuristic {


    @Override
    public int selectMove(MancalaBoard board,int depth){
        int player=board.currentPlayer();
        int bins=board.getBins();
        Scanner scanner=new Scanner(System.in);
        System.out.println("Please select a bin to move for player"+player);
        int bin=scanner.nextInt();
        while (board.getBin(bin)==0){
            System.err.println("Bin "+bin+" is empty. Please try again.");
            System.out.println("Please select a bin to move for player"+player);
            bin=scanner.nextInt();
        }
        System.out.println("ok");
        return bin;
    }
    @Override
    public int getHeuristicValue(MancalaBoard board){
        return 0;
    }

}
