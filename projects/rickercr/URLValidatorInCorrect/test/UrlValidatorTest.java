

import junit.framework.TestCase;
import java.util.Random;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;
//import junit.rules.ErrorCollector;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
    private final boolean printStatus = true;
    private final boolean printIndex = true;//print index that indicates current scheme,host,port,path, query test were using.
//   public ErrorCollector collector = new ErrorCollector();

    private String[] validScheme= new String[] {"https://", "http://", "ftp://" };
    private String[] invalidScheme= new String[] {"https:/", "htpt://", "fp::/" };
    private String[] validHost= new String[] {"www.google.com", "amazon.co.uk", "en.wikipedia.org"};
    private String[] invalidHost= new String[] {"www.google.romcom", "testing", "en.wikipedia."};
    private String[] validPort= new String[]{":80", ":3000", ":8080"};
    private String[] invalidPort= new String[]{":a80", ":30000000", "0"};
    private String[] validPath= new String[]{"/test", "/", "/search"};
    private String[] invalidPath= new String[]{"///", "/.../", "/test path name/"};

    public UrlValidatorTest(String testName) {
        super(testName);
    }


    public void testManualTest() {
        System.out.println("Running Manual Tests...");

        int numFails = 0;
        UrlValidator urlVal = new UrlValidator();

        assertTrue(urlVal.isValid("http://www.google.com"));
        assertFalse(urlVal.isValid("https:/www.google.com"));
        assertTrue(urlVal.isValid("http://amazon.co.uk"));
        assertTrue(urlVal.isValid("http://en.wikipedia.org"));
        assertFalse(urlVal.isValid("https://www.google.romcom"));
        assertTrue(urlVal.isValid("ftp://www.google.com"));
        assertFalse(urlVal.isValid("https://www.google.romcom:a80"));

        if (numFails > 0)
        {
            System.out.println("At least one manual test failed.");
        }
        else
        {
            System.out.println("Manual tests working as expected.");
        }

    }


    public void testYourFirstPartition() {
        System.out.println("Edge Invalid Testing");


        UrlValidator urlVal = new UrlValidator();

        //control test that should pass
        assertTrue(urlVal.isValid("https://www.example.com"));
        //should fail edge case for scheme
        assertFalse(urlVal.isValid("htp://www.example.com"));
        //should fail edge case for hostname
        assertFalse(urlVal.isValid("https://ww.example.com"));
        //should fail edge case for port number 0
        assertFalse(urlVal.isValid("https://www.example.com:0"));
        //should fail edge case for path as test does not exist
        assertFalse(urlVal.isValid("https://www.google.com:80/test"));
        //should fail edge case for query
        assertFalse(urlVal.isValid("http://en.wikipedia.org:80/.../"));
        //should fail edge case for scheme and port
        assertFalse(urlVal.isValid("https:/en.wikipedia.org:99999/test"));
        //should fail edge case for authority
        assertFalse(urlVal.isValid("ftp://www.google.romcom:80"));
        //should fail all part tests
        assertFalse(urlVal.isValid("fp::/en.wikipedia:a80///"));

        //all of the below should pass
        assertTrue(urlVal.isValid("http://www.google.com"));
        assertTrue(urlVal.isValid("https://amazon.co.uk"));
        assertTrue(urlVal.isValid("http://en.wikipedia.org:80"));
        assertTrue(urlVal.isValid("https://www.google.com/test"));
        assertTrue(urlVal.isValid("ftp://www.gmail.com:3000/"));
        assertTrue(urlVal.isValid("https://www.google.com:8080"));
        assertTrue(urlVal.isValid("ftp://en.wikipedia.org/search"));
        assertTrue(urlVal.isValid("http://amazon.co.uk:80/test"));
        assertTrue(urlVal.isValid(null));
  }



    public static String getRandom(String[] array) {
        int rnd = new Random().nextInt(array.length);
        return array[rnd];
    }
    //You need to create more test cases for your Partitions if you need to

    public void randomPart1() {
        System.out.println("Random Invalid Testing");


        UrlValidator urlVal = new UrlValidator();

        for (int i = 0; i < 10; i++) {
            String Scheme = getRandom(invalidScheme);
            String Host = getRandom(validHost);
            String Ports = getRandom(validPort);
            String Paths = getRandom(validPath);
            String URL = Scheme + Host + Ports + Paths;

            assertFalse(urlVal.isValid(URL));
        }

        for (int i = 0; i < 10; i++) {
            String Scheme = getRandom(validScheme);
            String Host = getRandom(invalidHost);
            String Ports = getRandom(validPort);
            String Paths = getRandom(validPath);
            String URL = Scheme + Host + Ports + Paths;

            assertFalse(urlVal.isValid(URL));
        }

        for (int i = 0; i < 10; i++) {
            String Scheme = getRandom(validScheme);
            String Host = getRandom(validHost);
            String Ports = getRandom(invalidPort);
            String Paths = getRandom(validPath);
            String URL = Scheme + Host + Ports + Paths;

            assertFalse(urlVal.isValid(URL));
        }

        for (int i = 0; i < 10; i++) {
            String Scheme = getRandom(validScheme);
            String Host = getRandom(validHost);
            String Ports = getRandom(validPort);
            String Paths = getRandom(invalidPath);
            String URL = Scheme + Host + Ports + Paths;

            assertFalse(urlVal.isValid(URL));
        }

        for (int i = 0; i < 10; i++) {
            String Scheme = getRandom(invalidScheme);
            String Host = getRandom(validHost);
            String Ports = getRandom(validPort);
            String Paths = getRandom(validPath);
            String URL = Host + Scheme + Ports + Paths;

            assertFalse(urlVal.isValid(URL));
        }

        System.out.println("Testing Complete");
    }

    public void randomPart2()
    {
        System.out.println("Running Random tests...");

        ResultPair[][] tests = getURLs();
        ResultPair[] schemes = tests[0];
        ResultPair[] authorities = tests[1];
        ResultPair[] ports = tests[2];
        ResultPair[] paths = tests[3];
        UrlValidator urlVal = new UrlValidator();
        int numFails = 0;

        for (int i = 0; i < schemes.length; i++) {
            for (int j = 0; j < authorities.length; j++) {
                for (int k = 0; k < ports.length; k++) {
                    for (int m = 0; m < paths.length; m++) {
                        boolean expected = schemes[i].valid && authorities[j].valid && ports[k].valid && paths[m].valid;
                        String url = schemes[i].item + authorities[j].item + ports[k].item + paths[m].item;
                        if (expected == true) {
                            assertTrue(urlVal.isValid(url));
                        }
                        else {
                            assertFalse(urlVal.isValid(url));
                        }
                    }
                }
            }
        }

        if (numFails > 0)
        {
            System.out.println("At least one manual test failed.");
        }
        else
        {
            System.out.println("Manual tests working as expected.");
        }
    }

    public static ResultPair[][] getURLs() {

        ResultPair[] testUrlScheme = {
                new ResultPair("http://", true),
                new ResultPair("ftp://", true),
                new ResultPair("https://", true),
                new ResultPair("http:/", false),
                new ResultPair("htpt://", false),
                new ResultPair("fp::/", false)
        };

        ResultPair[] testUrlAuthority = {
                new ResultPair("www.google.com", true),
                new ResultPair("amazon.co.uk", true),
                new ResultPair("www.gmail.com", true),
                new ResultPair("en.wikipedia.org", true),
                new ResultPair("www.google.romcom", false),
                new ResultPair("testing", false),
                new ResultPair("en.wikipedia", false)
        };

        ResultPair[] testUrlPort = {
                new ResultPair(":80", true),
                new ResultPair(":3000", true),
                new ResultPair(":8080", true),
                new ResultPair(":a80", false),
                new ResultPair(":0", false),
                new ResultPair(":30000000", false)
        };

        ResultPair[] testPath = {
                new ResultPair("/test", true),
                new ResultPair("/", true),
                new ResultPair("/search", true),
                new ResultPair("///", false),
                new ResultPair("/.../", false),
                new ResultPair("/test path name", false)
        };

        ResultPair[][] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath};
        return testUrlParts;
    }

    public void testIsValid() {
        assertTrue(true);
//      testManualTest();
    }
}






