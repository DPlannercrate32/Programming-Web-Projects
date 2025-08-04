import static java.nio.file.StandardOpenOption.*;
import java.nio.file.*;
import java.util.Scanner;
import java.io.*;

public class CreateWP {

  public static void main(String[] args) {

    // Convert the string to a
    // byte array.
	Scanner userin = new Scanner( System.in );
	Scanner css = new Scanner(System.in);
	String s = "<!DOCTYPE html>\n";
	String cssname;
	System.out.println("Give a Title!\n");
	s+="<head>\n";
	s+="<title>";
	s+=userin.nextLine();
	s+="</title>\n";
	System.out.println("Name your CSS file!\n");
	cssname = userin.nextLine();
	s+="<link rel=\'stylesheet\' href=\'" + cssname + ".css\' type=\'text/css\'/>\n";
    s+="</head>";
	System.out.println("Give a Header!\n");
	s+="<h1>";
	s+=userin.nextLine();
	s+="</h1>\n";
	System.out.println("Say anything!\n");
	s+="<body>\n";
	s+=userin.nextLine() + "\n";
	s+="</body>\n";
	s+="</html>\n";
	
	System.out.println("Give color of your Background!\n");
	String t = "body{\n Background-color: " + css.nextLine() + ";\n}";
	System.out.println("Give color of your header!\n");
	t += "h1{\n color: " + css.nextLine() + ";\n}";
	System.out.println("Give color of your text in the body!\n");
	t += "\nbody{\n color: " + css.nextLine() + ";\n}";
	 	
    byte data[] = s.getBytes();
    byte data2[] = t.getBytes();
    String d;
    System.out.println("Name your Html file!\n");
    d = userin.nextLine();
    System.out.println("Webpage created! Search the name of your created html and css files by using the Windows Search Bar!");
    Path p = Paths.get("./" + d + ".html");
    Path q = Paths.get("./" + cssname + ".css");
    
    try (OutputStream out = new BufferedOutputStream(
      Files.newOutputStream(p, CREATE, APPEND))) {
      out.write(data, 0, data.length);
    } catch (IOException x) {
      System.err.println(x);
    }
    try (OutputStream out = new BufferedOutputStream(
    	      Files.newOutputStream(q, CREATE, APPEND))) {
    	      out.write(data2, 0, data2.length);
    	    } catch (IOException x) {
    	      System.err.println(x);
    	    }
  }
}