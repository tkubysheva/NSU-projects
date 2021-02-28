package commands;
import java.util.Scanner;
import programContent.Content;

public class InputInt extends Command{
    @Override
    public void Action(Content content) {
        Scanner in = new Scanner(System.in);
        content.stack.push(in.nextInt());
    }
}
