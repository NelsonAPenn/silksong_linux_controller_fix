#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// In various places, I found the same config with different IDs. I've tried all of the below and have had success with none.
// static const char* const CONTROLLER_CONFIG="03000000c82d00001b30000001000000,8BitDo Ultimate 2C Wireless!,a:b0,b:b1,back:b10,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b6,leftstick:b13,lefttrigger:a5,leftx:a0,lefty:a1,paddle1:b2,paddle2:b5,rightshoulder:b7,rightstick:b14,righttrigger:a4,rightx:a2,righty:a3,start:b11,x:b3,y:b4,";
// static const char* const CONTROLLER_CONFIG="05000000c82d00001b30000001000000,8BitDo Ultimate 2C Wireless ,a:b0,b:b1,back:b10,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b6,leftstick:b13,lefttrigger:a5,leftx:a0,lefty:a1,paddle1:b5,paddle2:b2,rightshoulder:b7,rightstick:b14,righttrigger:a4,rightx:a2,righty:a3,start:b11,x:b3,y:b4,";
// static const char* const CONTROLLER_CONFIG="03000000c82d00001c30000001000000,8BitDo Ultimate 2C Wireless!,a:b0,b:b1,back:b10,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b12,leftshoulder:b6,leftstick:b13,lefttrigger:a5,leftx:a0,lefty:a1,paddle1:b2,paddle2:b5,rightshoulder:b7,rightstick:b14,righttrigger:a4,rightx:a2,righty:a3,start:b11,x:b3,y:b4,";
static const char* const CONTROLLER_CONFIG="0300604ec82d00000a31000014010000,8BitDo Ultimate 2C Wireless Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,crc:4e60,platform:Linux";

struct ControllerDefinition
{
  char guid[32];
  char name[64];
  size_t entry_length;
};

int seek_to_next_button_label_match(FILE* file)
{
  const char search[] = "SDL_GAMECONTROLLER_USE_BUTTON_LABELS";

  char c;
  int match = 0;
  size_t match_index = 0;
  for (size_t file_offset = 0; !feof(file); file_offset++)
  {
    c = fgetc(file);
    if (c == search[match_index])
    {
      if (match == 0)
      {
        match = 1;
      }
      match_index++;
      if (match_index == sizeof(search) - 1)
      {
        return 0;
        break;
      }
    }
    else if (match) {
      match = 0;
      match_index = 0;
    }
  }
  return 1;
}

/**
 * Seek to character after previous null character. Can be used to find beginning of a controller definition.
 */
void seek_to_item_start(FILE *file)
{
  char c;
  while((c = fgetc(file)) != '\0')
  {
    fseek(file, -2, SEEK_CUR);
  }
  
}

/**
 * Seek to the beginning of the item before the last null character. Need to check that it starts with GUID.
 */
void seek_to_previous_item(FILE *file)
{
  fseek(file, -2, SEEK_CUR);
  seek_to_item_start(file);
}

/**
 * Seek to next item
 */
void seek_to_next_item(FILE *file)
{
  char c;
  while((c = fgetc(file)) != '\0') { }
}

/**
 * Verify whether the bytes at cursor are a controller GUID.
 */
int guid_at_cursor(FILE* file, char* guid)
{
  size_t count = fread(guid, 1, 32, file);
  fseek(file, -count, SEEK_CUR);

  for (size_t j = 0; j < 32; j++)
  {
    if (!isxdigit(guid[j]))
    {
      return 0;
    }
  }
  return 1;
}

/**
 * Read basic controller information into def.
 */
void read_controller_entry(FILE* file, char* buf, struct ControllerDefinition* def)
{
  char c;

  size_t i = 0;
  for (; i < 1023 && (c = fgetc(file)) != '\0'; i++)
  {
    buf[i] = c;
  }
  
  buf[i] = 0;

  def->entry_length = i;
  strncpy(def -> guid, buf, 32);
  size_t j = 33;
  for(; buf[j] != ','; j++)
  {
    def->name[j - 33] = buf[j];
  }
  def -> name[j- 33] = '\0';
}

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s [path/to/UnityPlayer.so]\n", argv[0]);
    exit(1);
  }

  FILE* file = fopen(argv[1], "rb+");
  size_t target_length = strlen(CONTROLLER_CONFIG);
  printf("Target length %zu\n", target_length);

  char* buf = malloc(1024);
  size_t entry_num = 0;
  int found = 0;
  char guid[32];
  while (seek_to_next_button_label_match(file) == 0)
  {
    seek_to_item_start(file);
    if (!guid_at_cursor(file, guid))
    {
      continue;
    }
    while (1)
    {
      seek_to_previous_item(file);
      if (!guid_at_cursor(file, guid))
      {
        seek_to_next_item(file);
        break;
      }
    }

    while(guid_at_cursor(file, guid))
    {
      struct ControllerDefinition def;
      read_controller_entry(file, buf, &def);
      size_t entry_length = strlen(buf);

      printf("Controller: id %.32s, name %s, length %zu\n", def.guid, def.name, def.entry_length);

      if (entry_length == target_length)
      {
        printf("Replacing controller: id %.32s, name %s, length %zu\n", def.guid, def.name, def.entry_length);
        fseek(file, -(entry_length + 1), SEEK_CUR);
        fwrite(CONTROLLER_CONFIG, 1, (entry_length + 1), file);
      }
    }
    
  }

  free(buf);
  fclose(file);
  return 0;
}
