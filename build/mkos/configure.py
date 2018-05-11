
class Configure(object):

    def __init__(self,fname):
        self.entry=None
        self.inc_paths=[]
        self.src_paths=[]
        self.parse_config(fname)

    def parse_config(self,fname):
        with open(fname) as f:
            for line in f:
                line=line.replace('\n','').replace('\r','').strip()
                if not line or line[0]=='#':
                    continue
                if line[0:7]=='include':
                    self.inc_paths.append(line.split('+=')[1].strip())
                elif line[0:6]=='source':
                    self.src_paths.append(line.split('+=')[1].strip())


if __name__=='__main__':
    pass