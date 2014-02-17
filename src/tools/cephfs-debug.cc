
#include "include/types.h"
#include "common/config.h"
#include "common/ceph_argparse.h"
#include "global/global_init.h"
#include "mds/InoUtility.h"

void usage() {
  std::cerr << "Usage: \n"
      "    cephfs-debug by_id <inode id>\n"
      "    cephfs-debug by_path <path>\n"
      "    cephfs-debug simple_fsck\n";
}

int main(int argc, const char **argv)
{
  vector<const char*> args;
  argv_to_vec(argc, argv, args);
  env_to_vec(args);

  global_init(NULL, args, CEPH_ENTITY_TYPE_CLIENT, CODE_ENVIRONMENT_UTILITY, 0);
  common_init_finish(g_ceph_context);

  if (args.empty()) {
    usage();
    return -1;
  }

  std::cerr << args[0] << std::endl;

  InoUtility inou;
  inou.init();
  if (args[0] == std::string("by_id")) {
    inodeno_t ino = strtoll(args[1], NULL, 0);
    inou.by_id(ino);
  } else if (args[0] == std::string("by_path")) {
    std::string path = args[1];
    inou.by_path(path);
  } else if (args[0] == std::string("simple_fsck")) {
    inou.simple_fsck();
  } else {
    usage();
    inou.shutdown();
    return -1;
  }
  inou.shutdown();

  return 0;
}
