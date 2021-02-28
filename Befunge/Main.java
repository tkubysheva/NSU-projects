
public class Main {

    public static void main(String[] args) throws Exception {
        Interpreter interpreter = new Interpreter();
        interpreter.LoadFile(args[0]);
        interpreter.PlayField();
    }
}
