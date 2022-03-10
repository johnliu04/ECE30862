import java.io.*;
import java.util.*;
import java.io.IOException;

public class main {
    public static void main(String[] args) throws IOException {
        File file = new File(args[0]);
        BufferedReader bReader;
        bReader = new BufferedReader(new FileReader(file));
        bytecode bc = new bytecode(bReader);
        bc.compile();
    }
}
