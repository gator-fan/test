/*************************************************************************
 * @File Name: test.java
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年06月23日 星期二 14时50分23秒
 ************************************************************************/

class Test
{
  public static void main(String[] args)
  {
    //String s = "sslfan";
    //String s = "";
    String s = null;
    try{
      if(s.startsWith("ssl"))
      {
        s = s.substring(3);
        System.out.println("right");
        //System.out.println(news);
        System.out.println(s);
      }
      else
      {
        System.out.println("wrong");
      }
    } catch (Exception e) {    
      e.printStackTrace();
    }

  }
}
