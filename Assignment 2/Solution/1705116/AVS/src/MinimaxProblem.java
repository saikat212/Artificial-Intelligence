import java.util.ArrayList;

public interface MinimaxProblem {

    double heuristicValue();

    ArrayList<MinimaxProblem> successors();

    boolean isTerminal();
    boolean isMaximizing();
    boolean equals(MinimaxProblem o);
}
