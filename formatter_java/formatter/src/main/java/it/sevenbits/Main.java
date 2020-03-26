package it.sevenbits;

import it.sevenbits.formatter.IFormatter;
import it.sevenbits.lexer.ILexer;
import it.sevenbits.reader.FileReader;
import it.sevenbits.reader.IReader;
import it.sevenbits.reader.StringReader;
import it.sevenbits.state_machine.formatter.FormatterStateMachine;
import it.sevenbits.state_machine.lexer.LexerStateMachine;
import it.sevenbits.write.FileWriter;
import it.sevenbits.write.IWriter;
import it.sevenbits.write.StringWriter;

/**
 * The type Main.
 */
public final class Main {
    private Main() {
    }

    /**
     * Main.
     * test program
     *
     * @param args the args
     * @throws Exception the exception
     */
    public static void main(final String[] args) throws Exception {
        try {
            String path = args[0], filenameForReading = args[1], filenameForWriting = args[2];
            FileReader reader = new FileReader(path, filenameForReading);
            FileWriter writer = new FileWriter(path, filenameForWriting);


//        IReader reader = new StringReader("if (message == (\"text in kavichki\"))   " +
//                "{ int count=0; \n}  \n \n//comment it is     \n");                    //+++++
//        IReader reader = new StringReader("aaa {bbb ;   ccc   ;}        //p \0");               //+++++
//        IReader reader = new StringReader("{   {{  { }}  }    }");                    //+++++

//        IReader reader = new StringReader(
//                "if (message == (\"text into kavichki\"))\n" +
//                "{ int count=0; \n}  \n \n  //        comment it is     \n\n" +
//                "else {\n" +
//                "\n" +
//                "char   symb='z';}");
//
//            IWriter writer = new StringWriter();
            ILexer lexerState = new LexerStateMachine(reader);

            IFormatter formatter = new FormatterStateMachine();

            System.out.println("\n\n");

            formatter.format(lexerState, writer);


            writer.close();
            reader.close();
            System.out.println(writer.toString());
        } catch (Exception e) {
            System.out.println("error main");
        }
    }
}
