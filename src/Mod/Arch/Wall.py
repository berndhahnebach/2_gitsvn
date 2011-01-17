import FreeCAD,Part,Draft
from draftlibs import fcgeo
from FreeCAD import Vector

def makeWall(baseobj,width=None,height=None):
    '''makeWall(obj,[width],[height]): creates a wall based on the
    given object'''
    obj = FreeCAD.ActiveDocument.addObject("Part::FeaturePython","Wall")
    Wall(obj)
    ViewProviderWall(obj.ViewObject)
    obj.Base = baseobj
    if width: obj.Width = width
    if height: obj.Height = height
    return obj
            
class Wall:
    "The Wall object"
    def __init__(self,obj):
        obj.addProperty("App::PropertyLink","Base","Base",
                        "The base object this wall is built upon")
        obj.addProperty("App::PropertyLength","Width","Base",
                        "The width of this wall")
        obj.addProperty("App::PropertyLength","Height","Base",
                        "The height of this wall")
        obj.addProperty("App::PropertyEnumeration","Align","Base"
                        "The alignment of this wall on its base object, if applicable")
        obj.Align = ['Left','Right','Centered']
        obj.Proxy = self
        self.Type = "Wall"
        obj.Width = 0.1
        obj.Height = 1
        
    def execute(self,obj):
        self.createGeometry(obj)
        
    def onChanged(self,obj,prop):
        if prop in ["Base","Height","Width"]:
            self.createGeometry(obj)

    def createGeometry(self,obj):
            plm = obj.Placement
            if obj.Base:
                if Draft.getType(obj.Base) == "Wire":
                    dvec = fcgeo.vec(obj.Base.Shape.Edges[0]).cross(Vector(0,0,1))
                    dvec.normalize()
                    dvec = dvec.multiply(obj.Width)
                    base = Draft.offset(obj.Base,dvec,bind=True)
                    if obj.Height:
                        norm = fcgeo.getNormal(base)
                        norm = norm.multiply(obj.Height)
                        sol = base.extrude(norm)
                        obj.Shape = sol
                    else:
                        obj.Shape = base
            obj.Placement = plm

class ViewProviderWall:
    "A View Provider for the Wall object"
    def __init__(self,vobj):
        vobj.Proxy = self
        self.Object = vobj.Object

    def getIcon(self):          
        return """
                /* XPM */
                static char * arch_xpm[] = {
                "16 16 9 1",
                " 	c None",
                ".	c #543016",
                "+	c #6D2F08",
                "@	c #954109",
                "#	c #874C24",
                "$	c #AE6331",
                "%	c #C86423",
                "&	c #FD7C26",
                "*	c #F5924F",
                "                ",
                "                ",
                "       #        ",
                "      ***$#     ",
                "    .*******.   ",
                "   *##$****#+   ",
                " #**%&&##$#@@   ",
                ".$**%&&&&+@@+   ",
                "@&@#$$%&&@@+..  ",
                "@&&&%#.#$#+..#$.",
                " %&&&&+%#.$**$@+",
                "   @%&+&&&$##@@+",
                "     @.&&&&&@@@ ",
                "        @%&&@@  ",
                "           @+   ",
                "                "};
		"""
        
    def updateData(self,obj,prop):
        return

    def onChanged(self,vobj,prop):
        return

    def claimChildren(self):
        return [self.Object.Base]

    def attach(self,obj):
        return

    def getDisplayModes(self,obj):
        modes=[]
        return modes

    def setDisplayMode(self,mode):
        return mode

    def __getstate__(self):
        return None

    def __setstate__(self,state):
        return None


