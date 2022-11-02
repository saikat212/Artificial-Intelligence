


public abstract class MancalaHeuristic {
    static final int MAX_WEIGHT = 5;
    public int selectMove(MancalaBoard board,int depth)
    {
        int bin=0;
        try{
            bin=Minimax.minimax(board,depth)+1;
        } catch (Exception e){
            e.printStackTrace();
        }
        return  bin;
    }

    public  static MancalaHeuristic intToStrategy(int i) {
        if(i==1)
        {
            return new Heuristic1();
        }
        else if(i==2)
        {
            return new Heuristic2();
        }
        else if(i==3)
        {
            return new Heuristic3();
        }
        else if(i==4)
        {
            return new Heuristic4();

        }
        else if(i==5)
        {
            return new Heuristic5();
        }
        else if(i==6)
        {
            return new Heuristic6();
        }
        else
        {
            return new UserHeuristic();
        }

    }
    public abstract int getHeuristicValue(MancalaBoard board);

    public int selectMove1(MancalaBoard board,int depth)
    {
        int bin=0;
        try{
            bin=Minimax.minimax(board,depth)+1;


        } catch (Exception e){
            e.printStackTrace();
        }
        return  bin;
    }



}
