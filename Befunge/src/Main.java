
public class Main {

    public static void main(String[] args) throws Exception {
        Interpreter interpreter = new Interpreter();
        if(args.length == 0){
            System.out.println("Not enough arguments!!!");
            return;
        }
        interpreter.go(args[0]);
    }
}
